#ifndef IOA_INFERNO_STORAGE_H
#define IOA_INFERNO_STORAGE_H // Shared tree only; optional APK provisioning never uses private storage.
typedef struct AAssetManager AAssetManager; // Native asset source used only when provisioning is enabled.
#ifdef __cplusplus
extern "C" {
#endif
int ioa_prepare_storage(AAssetManager*);
#ifdef __cplusplus
}
#endif
#endif
