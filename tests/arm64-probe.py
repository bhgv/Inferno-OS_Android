#!/usr/bin/env python3
"""Exercise actual probe asset installation and result validation with real bounded host file I/O."""
from pathlib import Path
import os
import re
import shlex
import subprocess
import tempfile

ROOT = Path(__file__).resolve().parents[1]
SOURCE = Path(os.environ.get('ARM64_PROBE_SOURCE', ROOT/'app/src/main/cpp/arm64-probe/probe.cpp')).read_text()


# Extract a complete production function; only its fixed destination path is redirected into the fixture.
def function(name):
    start = re.search(r'\bstatic\s+(?:int|void)\s+\*?\s*'+re.escape(name)+r'\s*\(', SOURCE).start()
    opening = SOURCE.index('{', start)
    depth = 1
    at = opening+1
    while depth:
        depth += (SOURCE[at]=='{')-(SOURCE[at]=='}')
        at += 1
    return SOURCE[start:at]


# Run real stream and descriptor operations while mocking only Android assets and visible status publication.
def main():
    installer = function('install_probe')
    installer = installer.replace('"/sdcard/Inferno/dis/native64-apk/series0092-probe.dis64"','fixture_path')
    checker = function('check_result')
    directory = function('directory')
    starter = function('start_probe')
    unit = r'''
#include <sys/stat.h>
#include <pthread.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <vector>
#include <string>
#include <fstream>

#define AASSET_MODE_STREAMING 2 // Android stream access hint.
#define INFERNO_PROBE_JIT 1 // Independently require the JIT-selected completion marker.
struct AAssetManager {int unused;};
struct AAsset {
    size_t at; // Current immutable asset stream offset.
};
struct Probe {
    pthread_mutex_t lock; // Production retry state remains protected by a real mutex.
    pthread_t worker; // Observed mock thread identity; no unbounded join occurs in the fixture.
    int started, entered, failed; // Production lifecycle fields checked across consecutive taps.
    int logfd; // Real fixture descriptor consumed by production pread.
    off_t logstart; // Beginning of this session, excluding prior successful output.
};
static Probe state = {PTHREAD_MUTEX_INITIALIZER};
static std::vector<unsigned char> bytes(1317);
static const char *fixture_path;
static int deny, broken, closed, failed, created, joined, create_error;


/* Borrow the immutable asset payload and allocate a fresh independent stream cursor. */
static AAsset *AAssetManager_open(AAssetManager *, const char *name, int)
{
    if(strcmp(name,"native64/probe.dis64")!=0)return NULL;
    return new AAsset{0};
}


/* Publish the full known asset extent independently of read chunk sizes. */
static long AAsset_getLength(AAsset *) {return (long)bytes.size();}


/* Force short asset reads and optionally fail after a partially written destination. */
static int AAsset_read(AAsset *asset, void *buffer, size_t amount)
{
    if(broken && asset->at>=14)return -1;
    size_t count=bytes.size()-asset->at;
    if(count>amount)count=amount;
    if(count>7)count=7;
    memcpy(buffer,bytes.data()+asset->at,count);
    asset->at+=count;
    return (int)count;
}


/* Track closure on success, mismatch, denial and stream failure. */
static void AAsset_close(AAsset *asset) {closed++;delete asset;}


/* Simulate storage denial; all other descriptor operations reach the host filesystem. */
static int probe_open(const char *path,int flags,...)
{
    if(deny){errno=EACCES;return -1;}
    if(flags&O_CREAT){
        va_list args;va_start(args,flags);int mode=va_arg(args,int);va_end(args);
        return open(path,flags,mode);
    }
    return open(path,flags);
}


/* Record the real checker's success/failure decision without drawing a fake Android screen. */
static void status(const char *,int value) {failed=value;state.failed=value;}

#define open probe_open // Inject denial only around production provisioning.
INSTALLER
#undef open
DIRECTORY
CHECKER


/* Delay worker execution to expose a second tap before the new worker can clear stale failure state. */
static int fixture_create(pthread_t *thread,const pthread_attr_t *,void *(*)(void*),void*)
{
    if(create_error)return EAGAIN;
    *thread=(pthread_t)++created;
    return 0;
}


/* Observe joins deterministically; joining the newly created live VM would block the real UI forever. */
static int fixture_join(pthread_t,void**) {joined++;return 0;}


/* The mocked creator never enters a VM; only the production caller's lifecycle is under test here. */
static void *run_probe(void*) {return NULL;}

#define pthread_create fixture_create // Expose the pending-worker interleaving deterministically.
#define pthread_join fixture_join // Observe the join decision without hanging the test runner.
STARTER
#undef pthread_create
#undef pthread_join


/* Read existing bytes independently to detect accidental overwrite on any refusal. */
static std::string read_file(const char *path)
{
    std::ifstream stream(path,std::ios::binary);
    return std::string((std::istreambuf_iterator<char>(stream)),std::istreambuf_iterator<char>());
}


/* Exercise fresh/reused/mismatched assets, cleanup/retry, and session-specific completion witnesses. */
int main(int argc,char **argv)
{
    if(argc!=2)return 1;
    std::string path=std::string(argv[1])+"/probe.dis64";
    fixture_path=path.c_str();
    for(size_t i=0;i<bytes.size();i++)bytes[i]=(unsigned char)(i*17);
    if(!install_probe(NULL) || closed!=1 || read_file(fixture_path).size()!=bytes.size())return 2;
    std::string original=read_file(fixture_path);
    if(!install_probe(NULL) || closed!=2 || read_file(fixture_path)!=original)return 3;
    bytes[0]^=1;
    if(install_probe(NULL) || errno!=EINVAL || closed!=3 || read_file(fixture_path)!=original)return 4;
    bytes[0]^=1;
    deny=1;
    if(install_probe(NULL) || errno!=EACCES || closed!=4 || read_file(fixture_path)!=original)return 5;
    deny=0;unlink(fixture_path);broken=1;
    if(install_probe(NULL) || errno!=EIO || closed!=5 || access(fixture_path,F_OK)==0)return 6;
    broken=0;
    if(!install_probe(NULL) || closed!=6 || read_file(fixture_path)!=original)return 7;
    if(directory(fixture_path) || errno!=ENOTDIR)return 8;
    std::string folder=std::string(argv[1])+"/directory";
    if(!directory(folder.c_str()) || !directory(folder.c_str()))return 9;
    std::string log=std::string(argv[1])+"/probe.log";
    state.logfd=open(log.c_str(),O_RDWR|O_CREAT|O_TRUNC,0600);
    if(state.logfd<0)return 10;
    const char *good="native64 scalar module Native64AndroidProbe: jit=1, exit=\"\"\nnative64 scalar scheduler empty after program retirement\n";
    if(write(state.logfd,good,strlen(good))!=(ssize_t)strlen(good))return 14;
    state.logstart=lseek(state.logfd,0,SEEK_END);
    check_result();if(!failed)return 11;
    if(write(state.logfd,good,strlen(good))!=(ssize_t)strlen(good))return 14;
    check_result();if(failed)return 12;
    if(write(state.logfd,"Broken:",7)!=7)return 15;
    check_result();if(!failed)return 13;
    state.logstart=lseek(state.logfd,0,SEEK_END);
    if(write(state.logfd,good,strlen(good))!=(ssize_t)strlen(good))return 14;
    if(write(state.logfd,"panic: retirement failed",24)!=24)return 15;
    check_result();if(!failed)return 20;
    close(state.logfd);
    state.started=1;state.failed=1;state.entered=0;
    start_probe();
    if(created!=1 || joined!=1 || !state.started || state.failed)return 16;
    start_probe();
    if(created!=1 || joined!=1)return 17;
    state.entered=1;state.failed=1;
    start_probe();
    if(created!=1 || joined!=1)return 18;
    state.started=0;state.entered=0;create_error=1;
    start_probe();
    if(state.started || !state.failed)return 19;
    puts("PASS ARM64 probe production functions: exact reuse, no overwrite, short reads, denial, cleanup/retry, directory types, prior-session refusal, native-result validation and pending-worker double-tap refusal");
    return 0;
}
'''.replace('INSTALLER',installer).replace('DIRECTORY',directory).replace('CHECKER',checker).replace('STARTER',starter)
    with tempfile.TemporaryDirectory(prefix='arm64-probe-') as temporary:
        work=Path(temporary);(work/'test.cpp').write_text(unit)
        command=shlex.split(os.environ.get('CXX','c++'))
        command+=shlex.split(os.environ.get('CXXFLAGS','-O2 -g -fsanitize=undefined -fno-sanitize-recover=all'))
        subprocess.run(command+['-std=c++11',str(work/'test.cpp'),'-o',str(work/'test')],check=True)
        subprocess.run([str(work/'test'),str(work)],check=True)
        control=unit.replace(' && strstr(output, "panic:") == NULL', '')
        if control==unit:
            raise RuntimeError('Inactive panic-result control')
        (work/'test.cpp').write_text(control)
        subprocess.run(command+['-std=c++11',str(work/'test.cpp'),'-o',str(work/'test')],check=True)
        result=subprocess.run([str(work/'test'),str(work)])
        if result.returncode!=20:
            raise RuntimeError('Panic-result control did not expose false success')
        print('PASS active native-result control: completion markers cannot hide a retirement panic')


if __name__=='__main__':
    main()
