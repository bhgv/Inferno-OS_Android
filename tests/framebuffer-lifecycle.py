#!/usr/bin/env python3
"""Exercise the actual native command callback with changing Android window sizes."""
from pathlib import Path
import subprocess
import tempfile
ROOT = Path(__file__).resolve().parents[1]
bridge = (ROOT/'app/src/main/cpp/inferno_os_app.cpp').read_text()
a = bridge.index('static void\nProcessAndroidCmd(')
b = bridge.index('\n}', a)+2
source = r'''
#include <cstdio>
#include <cstdlib>
#include <cerrno>
#include <cstring>
#define ANDROID_LOG_ERROR 1 // Bounded diagnostic stub.
#define ANDROID_LOG_WARN 2 // Bounded diagnostic stub.
#define WINDOW_FORMAT_RGBX_8888 2 // Requested format only; dimensions must remain native.
#define LOGE(...) ((void)0) // Device logging has no lifecycle side effects.
#define LOGI(...) ((void)0) // Device logging has no lifecycle side effects.
enum {APP_CMD_INIT_WINDOW,APP_CMD_TERM_WINDOW,APP_CMD_LOST_FOCUS,APP_CMD_GAINED_FOCUS,
      APP_CMD_WINDOW_REDRAW_NEEDED,APP_CMD_WINDOW_RESIZED,APP_CMD_CONTENT_RECT_CHANGED,APP_CMD_DESTROY};
struct Window {int width,height;};
struct ANativeActivity {void *assetManager;};
struct ARect {int left,top,right,bottom;};
struct android_app {void *userData;Window *window;ANativeActivity *activity;int *config;};
static int Xsize,Ysize,boots,prepares,terminates,updates,pointer_resets,storage_calls,errors,refreshes;
static unsigned char pixel,*xscreendata;
static void *assetManager;
class Engine {
    android_app *app;
public:
    bool active;
    Engine(android_app *a):app(a),active(false){}
    void RefreshContent(){refreshes++;}
    ARect ContentBounds() const {return {0,90,app->window->width,app->window->height-78};}
    void CancelPointer(){pointer_resets++;}
    void PrepareDrawing(){prepares++;}
    void TerminateDisplay(){terminates++;active=false;}
    void StartAnimation(bool value){active=value;}
    void UpdateDisplay(){if(app->window==NULL)std::abort();updates++;}
};
static int AConfiguration_getDensity(int *density){return *density;}
static bool ioa_screen_size(ARect bounds,int density,int *w,int *h)
{
    if(bounds.left!=0||bounds.top!=90||bounds.right!=945||bounds.bottom!=1970||density!=420)std::abort();
    *w=416;*h=828;
    return true;
}
static int ANativeWindow_setBuffersGeometry(Window *w,int x,int y,int format)
{if(w==NULL||x!=0||y!=0||format!=2)std::abort();return 0;}
static int ioa_prepare_storage_progress(void*,void (*)(void),android_app*)
{return ++storage_calls==1?(errno=EACCES,-1):0;}
static void ioa_fb_storage_progress(void){}
static void ioa_status_screen(android_app*,const char *text,int)
{
    if(std::strstr(text,"/SDCARD/INFERNO")==NULL ||
       std::strstr(text,"THEN RETURN TO INFERNO")==NULL)
        std::abort();
    errors++;
}
static int __android_log_print(int,const char*,const char*,...){return 0;}
static int ioa_startup_log(){return 0;}
static void amain(){boots++;xscreendata=&pixel;}
'''
source += bridge[a:b]
source += r'''


/* Recreate and resume the surface without changing an already allocated logical framebuffer. */
int main()
{
    Window window={945,2048};ANativeActivity activity={NULL};int density=420;
    android_app app={NULL,&window,&activity,&density};Engine engine(&app);app.userData=&engine;
    ProcessAndroidCmd(&app,APP_CMD_INIT_WINDOW);
    if(boots!=0||errors!=1||engine.active)std::abort();
    ProcessAndroidCmd(&app,APP_CMD_GAINED_FOCUS);
    if(boots!=1||Xsize!=416||Ysize!=828||!engine.active)std::abort();
    ProcessAndroidCmd(&app,APP_CMD_LOST_FOCUS);
    if(engine.active||pointer_resets!=1)std::abort();
    ProcessAndroidCmd(&app,APP_CMD_GAINED_FOCUS);
    if(!engine.active||updates!=2)std::abort();
    app.window=NULL;ProcessAndroidCmd(&app,APP_CMD_TERM_WINDOW);
    ProcessAndroidCmd(&app,APP_CMD_GAINED_FOCUS);
    if(terminates!=1||pointer_resets!=2||engine.active)std::abort();
    window.width=480;window.height=280;app.window=&window;
    ProcessAndroidCmd(&app,APP_CMD_INIT_WINDOW);
    if(boots!=1||storage_calls!=2||Xsize!=416||Ysize!=828||prepares!=2||!engine.active)std::abort();
    ProcessAndroidCmd(&app,APP_CMD_WINDOW_RESIZED);
    ProcessAndroidCmd(&app,APP_CMD_WINDOW_REDRAW_NEEDED);
    ProcessAndroidCmd(&app,APP_CMD_CONTENT_RECT_CHANGED);
    if(Xsize!=416||Ysize!=828||updates!=6||refreshes!=7)std::abort();
    std::puts("PASS actual FB command callback: retry after shared-storage denial, startup once and stable logical dimensions");
}
'''
with tempfile.TemporaryDirectory(prefix='fb-lifecycle-',dir=ROOT) as directory:
    work=Path(directory);(work/'test.cpp').write_text(source)
    subprocess.run(['c++','-std=c++11','-fsanitize=undefined','-fno-sanitize-recover=all',
                    str(work/'test.cpp'),'-o',str(work/'test')],check=True)
    subprocess.run([str(work/'test')],check=True,timeout=10)
