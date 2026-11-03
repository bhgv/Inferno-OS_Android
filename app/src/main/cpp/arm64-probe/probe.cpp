#include <android_native_app_glue.h>
#include <android/asset_manager.h>
#include <android/input.h>
#include <android/native_activity.h>
#include <pthread.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include "../inferno_startup_screen.h"

#ifndef INFERNO_PROBE_JIT
#define INFERNO_PROBE_JIT 1 // Explicit test default; never inferred from the phone ABI.
#endif

struct ProbeState {
    pthread_mutex_t lock; // Protect progress and worker-to-UI notifications.
    pthread_t worker; // Main VM thread remains alive until this dedicated Activity process exits.
    android_app *app; // Activity borrow ends with process teardown.
    int started; // UI thread owns thread creation and retry decisions.
    int focused; // UI thread paints only while Android gives this window focus.
    int entered; // VM cannot be restarted within the same process.
    int failed; // Provisioning failed before entering the VM.
    int retired; // Core reports scheduler retirement through its native completion callback.
    int checked; // UI has checked this session's output exactly once.
    int logfd; // Open shared diagnostic file; also duplicated to stdout/stderr.
    off_t logstart; // Exclude earlier sessions when validating the result.
    char message[768]; // Bounded ASCII status independent of installed fonts.
};

static ProbeState state = {PTHREAD_MUTEX_INITIALIZER}; // One isolated probe VM per Activity process.

extern "C" void inferno_android_scalar_main(int, char**);


/* Publish status without calling Android drawing APIs from a VM or provisioning worker. */
static void status(const char *message, int failed)
{
    pthread_mutex_lock(&state.lock);
    snprintf(state.message, sizeof(state.message), "%s", message);
    state.failed = failed;
    pthread_mutex_unlock(&state.lock);
}


/* Create only the fixed shared tree path; existing non-directory components are errors. */
static int directory(const char *path)
{
    struct stat info;

    if(mkdir(path, 0775) != 0 && errno != EEXIST)
        return 0;
    if(stat(path, &info) != 0)
        return 0;
    if(!S_ISDIR(info.st_mode)){
        errno = ENOTDIR;
        return 0;
    }
    return 1;
}


/* Reuse an exact existing probe; never overwrite an unrelated or older shared image. */
static int install_probe(AAssetManager *manager)
{
    unsigned char buffer[1024], existing[1024];
    AAsset *asset = AAssetManager_open(manager, "native64/probe.dis64", AASSET_MODE_STREAMING);
    const char *path = "/sdcard/Inferno/dis/native64-apk/series0087-probe.dis64";
    int fd, owned, count, ok = 1, saved = 0;

    if(asset == NULL){ errno = ENOENT; return 0; }
    if(AAsset_getLength(asset) <= 0 || AAsset_getLength(asset) > 32768){
        AAsset_close(asset); errno = EFBIG; return 0;
    }
    fd = open(path, O_WRONLY|O_CREAT|O_EXCL, 0664);
    owned = fd >= 0;
    if(fd < 0 && errno == EEXIST)
        fd = open(path, O_RDONLY);
    if(fd < 0){ saved = errno; AAsset_close(asset); errno = saved; return 0; }
    while((count = AAsset_read(asset, buffer, sizeof(buffer))) > 0){
        int at = 0;
        while(at < count){
            ssize_t done = owned ? write(fd, buffer+at, count-at) : read(fd, existing+at, count-at);
            if(done < 0 && errno == EINTR) continue;
            if(done <= 0){ saved = done < 0 ? errno : EINVAL; ok = 0; break; }
            at += (int)done;
        }
        if(!ok) break;
        if(!owned && memcmp(buffer, existing, count) != 0){ saved = EINVAL; ok = 0; break; }
    }
    if(count < 0){ saved = EIO; ok = 0; }
    if(ok && !owned && read(fd, existing, 1) != 0){ saved = EINVAL; ok = 0; }
    if(ok && owned && fsync(fd) != 0){ saved = errno; ok = 0; }
    if(close(fd) != 0 && ok){ saved = errno; ok = 0; }
    if(!ok && owned) unlink(path);
    AAsset_close(asset);
    errno = saved;
    return ok;
}


/* Provision the fixed shared test image, open diagnostics, then enter the real ARM64 runtime. */
static void *run_probe(void *argument)
{
    char message[768];
    char *argv[] = {(char*)"android-arm64-fb", (char*)"-v", (char*)"-s", (char*)"-r",
        (char*)"/sdcard/Inferno", (char*)"-c", (char*)(INFERNO_PROBE_JIT ? "1" : "0"),
        (char*)"-d", (char*)"/dis/native64-apk/series0087-probe.dis64", NULL};
    (void)argument;

    status("ARM64 FB PROBE\nPREPARING /SDCARD/INFERNO\nNO PRIVATE RUNTIME DIRECTORY", 0);
    if(!directory("/sdcard/Inferno") || !directory("/sdcard/Inferno/dis") ||
       !directory("/sdcard/Inferno/dis/native64-apk") || !install_probe(state.app->activity->assetManager)){
        snprintf(message, sizeof(message), "ARM64 FB PROBE: STORAGE ERROR %d\nALLOW FILES / STORAGE IN ANDROID SETTINGS.\nCHECK /SDCARD/INFERNO.\nEXISTING PROBE FILES MUST MATCH THIS APK.\nTAP TO RETRY AFTER FIXING ACCESS.", errno);
        status(message, 1);
        return NULL;
    }
    state.logfd = open("/sdcard/Inferno/native64-fb-probe.log", O_RDWR|O_CREAT|O_APPEND, 0664);
    if(state.logfd < 0){ status("CANNOT OPEN /SDCARD/INFERNO/NATIVE64-FB-PROBE.LOG\nTAP TO RETRY AFTER FIXING ACCESS.", 1); return NULL; }
    state.logstart = lseek(state.logfd, 0, SEEK_END);
    if(state.logstart < 0 || dup2(state.logfd, STDOUT_FILENO) < 0 || dup2(state.logfd, STDERR_FILENO) < 0){
        close(state.logfd); state.logfd = -1;
        status("CANNOT REDIRECT SHARED DIAGNOSTICS.\nTAP TO RETRY.", 1); return NULL;
    }
    fprintf(stderr, "\nARM64 Android framebuffer probe; pointer-bytes=%zu; jit=%d\n", sizeof(void*), INFERNO_PROBE_JIT);
    fflush(stderr);
    snprintf(message, sizeof(message), "ARM64 FB PROBE\nRUNNING DIS64: JIT=%d\nCHECKING 4097 CALLS, CASE, INT/BIG/REAL\nLOG: /SDCARD/INFERNO/NATIVE64-FB-PROBE.LOG", INFERNO_PROBE_JIT);
    status(message, 0);
    pthread_mutex_lock(&state.lock);
    state.entered = 1;
    pthread_mutex_unlock(&state.lock);
    inferno_android_scalar_main(9, argv);
    status("ARM64 RUNTIME RETURNED BEFORE SCHEDULER RETIREMENT.\nCHECK NATIVE64-FB-PROBE.LOG", 1);
    return NULL;
}


/* Existing Android cleanexit calls this after the program and empty scheduler are reported. */
extern "C" void ioa_showsplash(void)
{
    pthread_mutex_lock(&state.lock);
    state.retired = 1;
    pthread_mutex_unlock(&state.lock);
}


/* Accept success only when this session records the named program, requested JIT mode and empty scheduler. */
static void check_result(void)
{
    char output[65537], marker[160];
    ssize_t count;

    count = pread(state.logfd, output, sizeof(output)-1, state.logstart);
    if(count < 0){ status("CANNOT READ THE PROBE RESULT LOG", 1); return; }
    output[count] = 0;
    snprintf(marker, sizeof(marker), "native64 scalar module Native64AndroidProbe: jit=%d, exit=\"\"", INFERNO_PROBE_JIT);
    if(strstr(output, marker) != NULL && strstr(output, "native64 scalar scheduler empty after program retirement") != NULL &&
       strstr(output, "Broken:") == NULL && strstr(output, "faults:") == NULL && strstr(output, "panic:") == NULL)
        status("PASS: ANDROID ARM64 DIS64\nPROGRAM COMPLETED AND SCHEDULER RETIRED\n4097 RESULT CALLS AND CASE PASSED\nINT/BIG/REAL RETURNS PASSED\nTHIS IS A SCALAR PROBE, NOT AWM.\nLOG: /SDCARD/INFERNO/NATIVE64-FB-PROBE.LOG\nBACK CLOSES THE PROBE.", 0);
    else
        status("FAIL: ARM64 DIS64 PROBE\nEXPECTED COMPLETION WAS NOT RECORDED.\nSEND /SDCARD/INFERNO/NATIVE64-FB-PROBE.LOG\nTHIS APK DOES NOT START AWM.", 1);
}


/* Retry only a completed provisioning failure; never create a second VM in this process. */
static void start_probe(void)
{
    int retry;

    pthread_mutex_lock(&state.lock);
    retry = state.failed && !state.entered;
    pthread_mutex_unlock(&state.lock);
    if(state.started){
        if(!retry) return;
        pthread_join(state.worker, NULL);
        state.started = 0;
    }
    pthread_mutex_lock(&state.lock);
    state.failed = 0;
    pthread_mutex_unlock(&state.lock);
    if(pthread_create(&state.worker, NULL, run_probe, NULL) != 0){ status("CANNOT START ARM64 PROBE WORKER. TAP TO RETRY.", 1); return; }
    state.started = 1;
}


/* Keep native lifecycle handling on the UI thread and provision only after the first valid window. */
static void command(android_app *app, int32_t event)
{
    if(event == APP_CMD_INIT_WINDOW && app->window != NULL)
        start_probe();
    if(event == APP_CMD_GAINED_FOCUS)
        state.focused = 1;
    if(event == APP_CMD_LOST_FOCUS || event == APP_CMD_TERM_WINDOW)
        state.focused = 0;
}


/* Back closes this dedicated VM Activity; a tap can retry storage access before VM entry. */
static int32_t input(android_app *app, AInputEvent *event)
{
    if(AInputEvent_getType(event) == AINPUT_EVENT_TYPE_KEY && AKeyEvent_getKeyCode(event) == AKEYCODE_BACK){
        if(AKeyEvent_getAction(event) == AKEY_EVENT_ACTION_UP) ANativeActivity_finish(app->activity);
        return 1;
    }
    if(AInputEvent_getType(event) == AINPUT_EVENT_TYPE_MOTION &&
       (AMotionEvent_getAction(event)&AMOTION_EVENT_ACTION_MASK) == AMOTION_EVENT_ACTION_UP){
        start_probe(); return 1;
    }
    return 0;
}


/* Render a native framebuffer status while the VM executes on its own worker and pthread context. */
extern "C" void android_main(android_app *app)
{
    char message[768];
    int retired;

    state.app = app;
    snprintf(state.message, sizeof(state.message), "ANDROID ARM64 FRAMEBUFFER PROBE\nWAITING FOR WINDOW");
    app->onAppCmd = command;
    app->onInputEvent = input;
    for(;;){
        android_poll_source *source;
        int events;
        int ident = ALooper_pollOnce(100, NULL, &events, (void**)&source);
        if(ident >= 0 && source != NULL) source->process(app, source);
        if(app->destroyRequested) _exit(0);
        pthread_mutex_lock(&state.lock);
        retired = state.retired;
        memcpy(message, state.message, sizeof(message));
        pthread_mutex_unlock(&state.lock);
        if(retired && !state.checked){ check_result(); state.checked = 1; }
        if(app->window != NULL && state.focused) ioa_status_screen(app, message, retired ? 100 : 10);
    }
}
