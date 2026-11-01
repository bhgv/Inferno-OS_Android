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
#define ANDROID_LOG_ERROR 1 // Bounded diagnostic stub.
#define ANDROID_LOG_WARN 2 // Bounded diagnostic stub.
#define WINDOW_FORMAT_RGBX_8888 2 // Requested format only; dimensions must remain native.
#define LOGE(...) ((void)0) // Device logging has no lifecycle side effects.
#define LOGI(...) ((void)0) // Device logging has no lifecycle side effects.
enum {APP_CMD_INIT_WINDOW,APP_CMD_TERM_WINDOW,APP_CMD_LOST_FOCUS,APP_CMD_GAINED_FOCUS,
      APP_CMD_WINDOW_REDRAW_NEEDED,APP_CMD_WINDOW_RESIZED,APP_CMD_DESTROY};
struct Window {int width,height;};
struct ANativeActivity {void *assetManager;};
struct android_app {void *userData;Window *window;ANativeActivity *activity;};
static int Xsize,Ysize,boots,prepares,terminates,updates,releases;
static unsigned char pixel,*xscreendata;
static void *assetManager;
class Engine {
    android_app *app;
public:
    bool active;
    Engine(android_app *a):app(a),active(false){}
    android_app *AndroidApp(){return app;}
    void PrepareDrawing(){prepares++;}
    void TerminateDisplay(){terminates++;active=false;}
    void StartAnimation(bool value){active=value;}
    void UpdateDisplay(){if(app->window==NULL)std::abort();updates++;}
};
static int ANativeWindow_getWidth(Window *w){return w->width;}
static int ANativeWindow_getHeight(Window *w){return w->height;}
static int ANativeWindow_setBuffersGeometry(Window *w,int x,int y,int format)
{if(w==NULL||x!=0||y!=0||format!=2)std::abort();return 0;}
static int ioa_prepare_storage_progress(void*,void (*)(void),android_app*){return 0;}
static void ioa_fb_storage_progress(void){}
static void ioa_status_screen(android_app*,const char*,int){}
static int __android_log_print(int,const char*,const char*,...){return 0;}
static int ioa_startup_log(){return 0;}
static void amain(){boots++;xscreendata=&pixel;}
static void goToFullscreenMode(ANativeActivity*){}
static void xmouse_btn(int,int,int buttons){if(buttons!=0)std::abort();releases++;}
'''
source += bridge[a:b]
source += r'''


/* Recreate and resume the surface without changing an already allocated logical framebuffer. */
int main()
{
    Window window={320,480};ANativeActivity activity={NULL};
    android_app app={NULL,&window,&activity};Engine engine(&app);app.userData=&engine;
    ProcessAndroidCmd(&app,APP_CMD_INIT_WINDOW);
    if(boots!=1||Xsize!=320||Ysize!=480||!engine.active)std::abort();
    ProcessAndroidCmd(&app,APP_CMD_LOST_FOCUS);
    if(engine.active||releases!=1)std::abort();
    ProcessAndroidCmd(&app,APP_CMD_GAINED_FOCUS);
    if(!engine.active||updates!=2)std::abort();
    app.window=NULL;ProcessAndroidCmd(&app,APP_CMD_TERM_WINDOW);
    ProcessAndroidCmd(&app,APP_CMD_GAINED_FOCUS);
    if(terminates!=1||engine.active)std::abort();
    window.width=480;window.height=280;app.window=&window;
    ProcessAndroidCmd(&app,APP_CMD_INIT_WINDOW);
    if(boots!=1||Xsize!=320||Ysize!=480||prepares!=2||!engine.active)std::abort();
    ProcessAndroidCmd(&app,APP_CMD_WINDOW_RESIZED);
    ProcessAndroidCmd(&app,APP_CMD_WINDOW_REDRAW_NEEDED);
    if(Xsize!=320||Ysize!=480||updates!=5)std::abort();
    std::puts("PASS actual FB command callback: startup once, focus resume, null-window termination and stable logical dimensions");
}
'''
with tempfile.TemporaryDirectory(prefix='fb-lifecycle-',dir=ROOT) as directory:
    work=Path(directory);(work/'test.cpp').write_text(source)
    subprocess.run(['c++','-std=c++11','-fsanitize=undefined','-fno-sanitize-recover=all',str(work/'test.cpp'),'-o',str(work/'test')],check=True)
    subprocess.run([str(work/'test')],check=True,timeout=10)
