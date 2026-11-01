#include <unistd.h>
#include <stdio.h>
#include <stdarg.h>
#include <dlfcn.h>

extern void inferno_android_scalar_main(int, char**);


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


/* Retire only the isolated CLI test process after the actual core reports its empty scheduler. */
void
ioa_showsplash(void)
{
    fflush(NULL);
    _exit(0);
}


/* Run the identical Android scalar entry used by the APK; the owning test checks its output. */
int
main(int argc, char **argv)
{
    inferno_android_scalar_main(argc, argv);
    return 2;
}
