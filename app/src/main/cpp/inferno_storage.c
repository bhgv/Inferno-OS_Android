#include "inferno_storage.h"
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


static const char *runtimefiles[] = { // Minimum phone desktop entry points, not every optional application.
	"dis/emuinit.dis", // Required AWM startup asset.
	"dis/sh.dis", // Required AWM startup asset.
	"dis/wm/awm.dis", // Required AWM startup asset.
	"dis/wm/atoolbar.dis", // Required AWM startup asset.
	"dis/wm/keyboard.dis", // Required AWM startup asset.
	"dis/wm/sh.dis", // Required AWM startup asset.
	"dis/lib/arg.dis", // Required AWM startup asset.
	"dis/lib/string.dis", // Required AWM startup asset.
	"dis/lib/wmsrv.dis", // Required AWM startup asset.
	"dis/lib/wmclient.dis", // Required AWM startup asset.
	"dis/lib/winplace.dis", // Required AWM startup asset.
	"dis/lib/tkclient.dis", // Required AWM startup asset.
	"dis/lib/wmlib.dis", // Required AWM startup asset.
	"dis/lib/titlebar.dis", // Required AWM startup asset.
	"lib/awmsetup", // Required AWM startup asset.
	"fonts/ttf/Vera.ttf", // Required AWM startup asset.
	"dis/sh/std.dis", // Toolbar startup shell builtins.
	"fonts/ttf/FantasqueSansMono-Regular.ttf", // Default bundled command-line font.
};


static const char *runtimedirs[] = { // Required native namespace mount points.
	"chan", "dev", "env", "fd", "mnt", "net", "prog", "srv", "tmp", "usr/inferno"
};


/* Prefer a complete user tree and never enumerate APK assets on this fast path. */
int
ioa_runtime_ready(void)
{
	char path[4096];
	struct stat state;
	unsigned int i;
	int bytes;

	if(stat("/sdcard/Inferno", &state) != 0 || !S_ISDIR(state.st_mode) ||
	   access("/sdcard/Inferno", R_OK|W_OK|X_OK) != 0)
		return 0;
	for(i=0; i<sizeof(runtimefiles)/sizeof(runtimefiles[0]); i++){
		bytes = snprintf(path, sizeof(path), "/sdcard/Inferno/%s", runtimefiles[i]);
		if(bytes < 0 || (size_t)bytes >= sizeof(path) || stat(path, &state) != 0 ||
		   !S_ISREG(state.st_mode) || state.st_size <= 0 || access(path, R_OK) != 0)
			return 0;
	}
	for(i=0; i<sizeof(runtimedirs)/sizeof(runtimedirs[0]); i++){
		bytes = snprintf(path, sizeof(path), "/sdcard/Inferno/%s", runtimedirs[i]);
		if(bytes < 0 || (size_t)bytes >= sizeof(path) || stat(path, &state) != 0 ||
		   !S_ISDIR(state.st_mode) || access(path, R_OK|W_OK|X_OK) != 0)
			return 0;
	}
	return 1;
}


#ifndef INFERNO_BUNDLE_RUNTIME
#define INFERNO_BUNDLE_RUNTIME 0 // APK runtime provisioning is explicitly opt-in.
#endif

#if INFERNO_BUNDLE_RUNTIME
#include <android/asset_manager.h>
#include <stdio.h>
#include <string.h>

#define StoragePath 4096 // Bound complete native paths and asset names without truncation.
#define ManifestLimit (4*1024*1024) // Bound the bundled file index before allocating its buffer.


/* Create missing shared-tree directories, refusing a conflicting regular file. */
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
installassets(const char *root, AAssetManager *manager, IoaStorageProgress progress, void *argument)
{
	AAsset *asset;
	char *manifest, *line, *end, path[StoragePath];
	off_t length;
	size_t used;
	int bytes, result;
	unsigned int total = 0, done = 0, i;
	unsigned char found[sizeof(runtimefiles)/sizeof(runtimefiles[0])] = {0};

	asset = manager == NULL ? NULL : AAssetManager_open(manager, "inferno/manifest.txt", AASSET_MODE_BUFFER);
	if(asset == NULL){
		errno = ENOENT;
		return -1;
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
	/* Validate the complete index and count files before mutating shared storage. */
	for(line = manifest; result == 0 && *line != '\0'; line = end+1){
		end = strchr(line, '\n');
		if(end == NULL){ result = -1; break; }
		*end = '\0';
		if((line[0] != 'D' && line[0] != 'F') || line[1] != '\t' || !relativepath(line+2))
			result = -1;
		else if(line[0] == 'F'){
			total++;
			for(i=0; i<sizeof(runtimefiles)/sizeof(runtimefiles[0]); i++)
				if(strcmp(line+2, runtimefiles[i]) == 0)
					found[i] = 1;
		}
		*end = '\n';
	}
	for(i=0; result == 0 && i<sizeof(runtimefiles)/sizeof(runtimefiles[0]); i++)
		if(!found[i]){
			fprintf(stderr, "Inferno APK is missing required AWM asset: %s\n", runtimefiles[i]);
			errno = ENOENT;
			result = -1;
		}
	if(result == 0 && progress != NULL && !progress(0, total, "Preparing /sdcard/Inferno", argument)){
		errno = ECANCELED;
		result = -1;
	}
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
		if(progress != NULL && !progress(done, total, line+2, argument)){
			errno = ECANCELED;
			result = -1;
			break;
		}
		bytes = snprintf(path, sizeof(path), "%s/%s", root, line+2);
		if(bytes < 0 || (size_t)bytes >= sizeof(path))
			result = -1;
		else if(line[0] == 'D')
			result = makedirectory(path);
		else {
			result = installfile(root, line+2, manager);
			if(result == 0){
				done++;
				if(progress != NULL && !progress(done, total, line+2, argument)){
					errno = ECANCELED;
					result = -1;
				}
			}
		}
		if(result != 0)
			fprintf(stderr, "Inferno extraction failed: %s (errno=%d)\n", path, errno);
	}
	free(manifest);
	return result;
}


#endif


/* Reuse complete shared trees immediately; provision missing entries only when needed. */
int
ioa_prepare_storage_progress(AAssetManager *manager, IoaStorageProgress progress, void *argument)
{
	if(ioa_runtime_ready())
		return setenv("EXTERNAL_STORAGE", "/sdcard", 1);
#if INFERNO_BUNDLE_RUNTIME
	if(makedirectory("/sdcard/Inferno") != 0 ||
	   installassets("/sdcard/Inferno", manager, progress, argument) != 0)
		return -1;
#else
	(void)manager; (void)progress; (void)argument;
#endif
	if(!ioa_runtime_ready()){
		fprintf(stderr, "Inferno AWM runtime incomplete: need dis/wm/awm.dis, atoolbar and dependencies in /sdcard/Inferno\n");
		errno = ENOENT;
		return -1;
	}
	return setenv("EXTERNAL_STORAGE", "/sdcard", 1);
}


/* Preserve native launcher ABI while sharing the complete-tree fast path. */
int
ioa_prepare_storage(AAssetManager *manager)
{
	return ioa_prepare_storage_progress(manager, NULL, NULL);
}


/* Append native VM diagnostics in the shared tree so a silent desktop can be diagnosed on-device. */
int
ioa_startup_log(void)
{
	int fd;

	fd = open("/sdcard/Inferno/startup.log", O_WRONLY|O_CREAT|O_APPEND, 0600);
	if(fd < 0)
		return -1;
	if(dup2(fd, 1) < 0 || dup2(fd, 2) < 0){
		close(fd);
		return -1;
	}
	if(fd != 1 && fd != 2)
		close(fd);
	setvbuf(stdout, NULL, _IOLBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
	fprintf(stderr, "\nInferno VM startup: /sdcard/Inferno; expected phone desktop /dis/wm/awm.dis\n");
	return 0;
}
