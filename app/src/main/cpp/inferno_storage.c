#include "inferno_storage.h"
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define StoragePath 4096 // Bound complete native paths and asset names without truncation.
#define ManifestLimit (4*1024*1024) // Bound the bundled file index before allocating its buffer.


/* Create app-owned directories, refusing a conflicting regular file. */
static int
makedirectory(const char *path)
{
	struct stat state;

	if(mkdir(path, 0700) != 0 && errno != EEXIST)
		return -1;
	if(stat(path, &state) != 0)
		return -1;
	if(!S_ISDIR(state.st_mode)){
		errno = ENOTDIR;
		return -1;
	}
	return 0;
}


/* Accept only complete relative components produced by the runtime staging script. */
static int
relativepath(const char *name)
{
	const char *part, *end;
	size_t bytes;

	if(name[0] == '\0' || name[0] == '/')
		return 0;
	for(part = name; *part != '\0'; part = end+1){
		end = strchr(part, '/');
		bytes = end == NULL ? strlen(part) : (size_t)(end-part);
		if(bytes == 0 || (bytes == 1 && part[0] == '.') ||
		   (bytes == 2 && part[0] == '.' && part[1] == '.'))
			return 0;
		if(end == NULL)
			return 1;
	}
	return 0;
}


/* Copy a missing asset through a temporary file; preserve existing user files. */
static int
installfile(const char *root, const char *name, AAssetManager *manager)
{
	char destination[StoragePath], temporary[StoragePath], assetname[StoragePath], buffer[16384];
	AAsset *asset;
	FILE *file;
	struct stat state;
	int bytes, result;

	bytes = snprintf(destination, sizeof(destination), "%s/%s", root, name);
	if(bytes < 0 || (size_t)bytes >= sizeof(destination))
		return -1;
	if(stat(destination, &state) == 0)
		return S_ISREG(state.st_mode) ? 0 : -1;
	bytes = snprintf(temporary, sizeof(temporary), "%s.inferno-install", destination);
	if(bytes < 0 || (size_t)bytes >= sizeof(temporary))
		return -1;
	bytes = snprintf(assetname, sizeof(assetname), "inferno/%s", name);
	if(bytes < 0 || (size_t)bytes >= sizeof(assetname))
		return -1;
	asset = AAssetManager_open(manager, assetname, AASSET_MODE_STREAMING);
	if(asset == NULL)
		return -1;
	file = fopen(temporary, "wb");
	if(file == NULL){
		AAsset_close(asset);
		return -1;
	}
	result = 0;
	while((bytes = AAsset_read(asset, buffer, sizeof(buffer))) > 0){
		if(fwrite(buffer, 1, bytes, file) != (size_t)bytes){
			result = -1;
			break;
		}
	}
	if(bytes < 0)
		result = -1;
	if(fclose(file) != 0)
		result = -1;
	AAsset_close(asset);
	if(result == 0)
		result = rename(temporary, destination);
	if(result != 0)
		unlink(temporary);
	return result;
}


/* Install the bounded index in parent-first order before starting any Inferno process. */
static int
installassets(const char *root, AAssetManager *manager)
{
	AAsset *asset;
	char *manifest, *line, *end, path[StoragePath];
	off_t length;
	size_t used;
	int bytes, result;

	asset = manager == NULL ? NULL : AAssetManager_open(manager, "inferno/manifest.txt", AASSET_MODE_BUFFER);
	if(asset == NULL){
		/* Keep manually provisioned roots usable with older APK packaging. */
		bytes = snprintf(path, sizeof(path), "%s/dis/emuinit.dis", root);
		return bytes > 0 && (size_t)bytes < sizeof(path) && access(path, R_OK) == 0 ? 0 : -1;
	}
	length = AAsset_getLength(asset);
	if(length <= 0 || length > ManifestLimit){
		AAsset_close(asset);
		return -1;
	}
	manifest = malloc((size_t)length+1);
	if(manifest == NULL){
		AAsset_close(asset);
		return -1;
	}
	used = 0;
	while(used < (size_t)length && (bytes = AAsset_read(asset, manifest+used, (size_t)length-used)) > 0)
		used += bytes;
	AAsset_close(asset);
	manifest[used] = '\0';
	result = used == (size_t)length && strlen(manifest) == used ? 0 : -1;
	for(line = manifest; result == 0 && *line != '\0'; line = end+1){
		end = strchr(line, '\n');
		if(end == NULL){
			result = -1;
			break;
		}
		*end = '\0';
		if((line[0] != 'D' && line[0] != 'F') || line[1] != '\t' || !relativepath(line+2)){
			result = -1;
			break;
		}
		bytes = snprintf(path, sizeof(path), "%s/%s", root, line+2);
		if(bytes < 0 || (size_t)bytes >= sizeof(path))
			result = -1;
		else if(line[0] == 'D')
			result = makedirectory(path);
		else
			result = installfile(root, line+2, manager);
	}
	free(manifest);
	return result;
}


/* NativeActivity supplies its private data path; no Java code or JNI call is involved. */
int
ioa_prepare_storage(const char *internal, AAssetManager *manager)
{
	char root[StoragePath];
	int bytes;

	if(internal == NULL || internal[0] != '/')
		return -1;
	bytes = snprintf(root, sizeof(root), "%s/Inferno", internal);
	if(bytes < 0 || (size_t)bytes >= sizeof(root) || makedirectory(root) != 0)
		return -1;
	if(installassets(root, manager) != 0)
		return -1;
	/* The second variable also supports the bundled older amain implementation. */
	if(setenv("INFERNO_FILES_DIR", internal, 1) != 0 || setenv("EXTERNAL_STORAGE", internal, 1) != 0)
		return -1;
	return 0;
}
