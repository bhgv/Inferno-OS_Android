#ifndef IOA_INFERNO_STORAGE_H
#define IOA_INFERNO_STORAGE_H // Shared tree only; optional APK provisioning never uses private storage.
typedef struct AAssetManager AAssetManager; // Native asset source used only when provisioning is enabled.
#ifdef __cplusplus
extern "C" {
#endif
typedef int (*IoaStorageProgress)(unsigned int, unsigned int, const char*, void*); // Return zero to cancel between files.


/* Validate the existing phone UI tree without opening APK assets. */
int ioa_runtime_ready(void);


/* Append native VM stdout/stderr to the shared startup log without replacing user files. */
int ioa_startup_log(void);


/* Report completed file entries; total is known before extraction begins. */
int ioa_prepare_storage_progress(AAssetManager*, IoaStorageProgress, void*);


/* Compatibility entry for native launchers without a progress surface. */
int ioa_prepare_storage(AAssetManager*);
#ifdef __cplusplus
}
#endif
#endif

