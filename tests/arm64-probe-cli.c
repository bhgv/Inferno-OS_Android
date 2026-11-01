#include <unistd.h>
#include <stdio.h>
#include <stdarg.h>
#include <dlfcn.h>
#include <pthread.h>

extern void inferno_android_scalar_main(int, char**);

static __thread int probe_retired; // Only the retiring VM worker may complete the CLI witness.

static __thread volatile unsigned char probe_tls[64] __attribute__((aligned(64))); // Real Bionic ELF TLS extent/alignment and thread-isolation witness.


/* QEMU/Linux has no Android log daemon; real descriptor output remains independently checked. */
int
__android_log_print(int priority, const char *tag, const char *format, ...)
{
    (void)priority;
    (void)tag;
    (void)format;
    return 0;
}


/* Static Bionic has no dynamic Android loader; symbolize nothing in this test-only adapter. */
int
dladdr(const void *address, Dl_info *information)
{
    (void)address;
    (void)information;
    return 0;
}


/* Let Android cleanexit continue through actual pexit and allocator cleanup. */
void
ioa_showsplash(void)
{
    if(probe_tls[0] != 0)
        _exit(3);
    probe_retired = 1;
}


/* Observe pthread exit only after the real worker has freed its environment and Proc. */
void
__wrap_pthread_exit(void *result)
{
    if(probe_retired){
        fflush(NULL);
        _exit(0);
    }
    extern void __real_pthread_exit(void*);
    __real_pthread_exit(result);
    _exit(4);
}


/* Run the identical Android scalar entry used by the APK; the owning test checks its output. */
int
main(int argc, char **argv)
{
    probe_tls[0] = 0x5a;
    inferno_android_scalar_main(argc, argv);
    return 2;
}
