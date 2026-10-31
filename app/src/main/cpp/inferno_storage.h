#ifndef IOA_INFERNO_STORAGE_H
#define IOA_INFERNO_STORAGE_H // Native startup storage and bundled filesystem deployment.
#include <android/asset_manager.h>
#ifdef __cplusplus
extern "C" {
#endif
int ioa_prepare_storage(const char*, AAssetManager*);
#ifdef __cplusplus
}
#endif
#endif
