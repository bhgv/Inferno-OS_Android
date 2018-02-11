
#include <cstdio>
#include <cassert>

#include <android/window.h>
#include <android/native_activity.h>

#include <android/native_window.h>
#include <android_native_app_glue.h>

#include <android/input.h>

//#include "utils.h"


#include <android/log.h>


#define  LOG_TAG    "inferno SO"
#define  LOGI(...)  //__android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGW(...)  //__android_log_print(ANDROID_LOG_WARN,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  //__android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)


#define MBUTS_ACCORD_OTHER_KEY_BORDER  1000000000

typedef unsigned long long uint64;
typedef unsigned int uint32;


const int kFRAME_DISPLAY_TIME = 1;


void goToFullscreenMode(ANativeActivity* activity);


extern "C" {
	//extern
	int Xsize = 640;
	//extern
	int Ysize = 480;

	unsigned char *xscreendata = NULL; 

	extern void amain();
	extern void xmouse_btn(int x, int y, int btn);
	extern void xexpose();
}


extern "C" {

	int is_int_refresh = 0;
	int xb, xe, yb, ye;

	void int_refresh(int xb_, int yb_, int xe_, int ye_){
		if(is_int_refresh){
			if(xb > xb_)
				xb = xb_;
			if(yb > yb_)
				yb = yb_;
			if(xe < xe_)
				xe = xe_;
			if(ye < ye_)
				ye = ye_;
		}else{
			xb = xb_;
			xe = xe_;
			yb = yb_;
			ye = ye_;
		}

		is_int_refresh = 1;
	}

}



class Engine {
  public:
    explicit Engine(android_app* app) :
                app_(app),
                animating_(false) {
        memset(&frameStartTime_, 0, sizeof(frameStartTime_));
        memset(&smallFrameStartTime_, 0, sizeof(smallFrameStartTime_));
    }

    ~Engine() {}

    struct android_app* AndroidApp(void) const { return app_; }
    void StartAnimation(bool start) { animating_ = start; }
    bool IsAnimating(void) const { return animating_; }
    void TerminateDisplay(void) { 
		StartAnimation(false);
		
//		delete[] xscreendata;
//		xscreendata = NULL;
	}

     // PrepareDrawing(): Initialize the Engine with current native window geometry
     //   and blank current screen to avoid garbbage displaying on device
    bool PrepareDrawing(void);

    bool UpdateDisplay(void);

  private:
    void UpdateFrameBuffer(ANativeWindow_Buffer* buf, uint8_t* src);
    struct android_app* app_;
    bool animating_;
    struct timespec frameStartTime_;
    struct timespec smallFrameStartTime_;
};


static int32_t ProcessAndroidInput(struct android_app *app, AInputEvent *event) {
	static int mbtns = 0;
	static int x, y;
	static int id;
	static uint64 first_tap_time = 0;
    Engine* engine = reinterpret_cast<Engine*>(app->userData);
	switch(AInputEvent_getType(event)){
		case AINPUT_EVENT_TYPE_MOTION:
			{
				int32_t action = AMotionEvent_getAction( event ) & AMOTION_EVENT_ACTION_MASK;
				switch(action){
					case AMOTION_EVENT_ACTION_MOVE:
						{
							x = AMotionEvent_getX( event, 0 );
							y = AMotionEvent_getY( event, 0 );
LOGI("m move X=%d, Y=%d, mbtns=%d", x, y, mbtns );
							xmouse_btn(x, y, mbtns);
						}
						break;

					case AMOTION_EVENT_ACTION_DOWN:
						{
							uint64 tap_time = AMotionEvent_getEventTime(event);

							mbtns = AMotionEvent_getPointerCount(event);
							if(mbtns == 1){
								id = AMotionEvent_getPointerId(event, 0);
								first_tap_time = tap_time;
								x = AMotionEvent_getX(event, 0);
								y = AMotionEvent_getY(event, 0);
							}else //if(tap_time - first_tap_time > MBUTS_ACCORD_OTHER_KEY_BORDER)
							{
								xmouse_btn(x, y, 0);
							}
LOGI("m touch X=%d, Y=%d, mbtns=%d, t=%d:%d", x, y, mbtns, (uint32)(tap_time>>32), (uint32)tap_time);
							xmouse_btn(x, y, mbtns);
							//return 1;
						}
						break;
						
					case AMOTION_EVENT_ACTION_POINTER_DOWN:
						{
							uint64 tap_time = AMotionEvent_getEventTime(event);
							if(tap_time - first_tap_time > MBUTS_ACCORD_OTHER_KEY_BORDER){
								xmouse_btn(x, y, 0);
							}
							//x = AMotionEvent_getX(event, 0);
							//y = AMotionEvent_getY(event, 0);
//								xmouse_btn(x, y, 0);
							
							mbtns = AMotionEvent_getPointerCount(event);
LOGI("m multi( %d )touch X=%d, Y=%d, dt=%d", mbtns, x, y, tap_time - first_tap_time);
							xmouse_btn(x, y, 0);
							xmouse_btn(x, y, mbtns);
						}
						break;

					case AMOTION_EVENT_ACTION_UP:
						{
							if( id == AMotionEvent_getPointerId(event, 0) ){
								x = AMotionEvent_getX(event, 0);
								y = AMotionEvent_getY(event, 0);
LOGI("m un touch X=%d, Y=%d, mbtns=%d", x, y, mbtns );
								xmouse_btn(x, y, 0);
								mbtns = 0;
							}
						}
						break;

				};
        		engine->StartAnimation(true);
        		return 1;
    		}

		case AINPUT_EVENT_TYPE_KEY:
			{
LOGI("Key event: action=%d keyCode=%d metaState=0x%x",
		                AKeyEvent_getAction(event),
		                AKeyEvent_getKeyCode(event),
		                AKeyEvent_getMetaState(event));
				break;
			}
    }

    return 0;
}


extern "C" {
	
#define LCT_RGBA  6 /*RGB with alpha: 8,16 bit*/

typedef unsigned int LodePNGColorType;

extern void free_(void *v);

extern unsigned lodepng_decode_memory(unsigned char** out, unsigned* w, unsigned* h, unsigned char* buffer, size_t buffersize,
								 LodePNGColorType colortype, unsigned bitdepth);

void lodepng_free(unsigned char* buffer){ free_((void*)buffer); }


AAssetManager* assetManager = NULL;


void ioa_showsplash(){
	if(assetManager == NULL || xscreendata == NULL) return;
	
	char filePath[] = "images/splash.png";
	AAsset* file = AAssetManager_open(assetManager, filePath, AASSET_MODE_BUFFER);
	size_t fileLength = AAsset_getLength(file);
	
	char* fileContent = new char[fileLength+1];
	
	AAsset_read(file, fileContent, fileLength);
	fileContent[fileLength] = '\0';
	
	unsigned char* buffer = NULL;
	unsigned error;
	unsigned w, h;
	
	error = lodepng_decode_memory(&buffer, &w, &h, (unsigned char*)fileContent, fileLength, LCT_RGBA, 8);

	int x0, y0;

	if(Xsize >= Ysize){
		x0 = (Xsize - w) / 2;
		y0 = (Ysize - h) / 2;
	}else{
		x0 = (Ysize - w) / 2;
		y0 = (Xsize - h) / 2;
	}
	
	for(int i = 0; i < Ysize; i++){
		for(int j = 0; j < Xsize*4; j += 4){
			xscreendata[ i*Xsize*4 + j + 0] = 0;
			xscreendata[ i*Xsize*4 + j + 1] = 0;
			xscreendata[ i*Xsize*4 + j + 2] = 0;
			xscreendata[ i*Xsize*4 + j + 3] = 0xff;
		}
	}

	if(buffer)
	for(int i = 0; i < Ysize; i++){
		for(int j = 0; j < Xsize; j += 1){
			int x, y;
			if(Xsize >= Ysize){
				x = j - x0; y = i - y0;
				if( x >= 0 && x < w && y >= 0 && y < h){
					xscreendata[ i*Xsize*4 + j*4 + 0] = buffer[y*w*4 + x*4 + 2];
					xscreendata[ i*Xsize*4 + j*4 + 1] = buffer[y*w*4 + x*4 + 1];
					xscreendata[ i*Xsize*4 + j*4 + 2] = buffer[y*w*4 + x*4 + 0];
					xscreendata[ i*Xsize*4 + j*4 + 3] = 0xff; //buffer[i*w*4 + j + 3];
				}
			}else{
				x = i - x0; y = j - y0;
				if( x >= 0 && x < w && y >= 0 && y < h ){
					y = h - y;
					xscreendata[ i*Xsize*4 + j*4 + 0] = buffer[y*w*4 + x*4 + 2];
					xscreendata[ i*Xsize*4 + j*4 + 1] = buffer[y*w*4 + x*4 + 1];
					xscreendata[ i*Xsize*4 + j*4 + 2] = buffer[y*w*4 + x*4 + 0];
					xscreendata[ i*Xsize*4 + j*4 + 3] = 0xff; //buffer[i*w*4 + j + 3];
				}
			}
		}
	}

	lodepng_free(buffer);
	delete[] fileContent;
}

} // extern "C"


static void ProcessAndroidCmd(struct android_app *app, int32_t cmd) {
    static int32_t format = WINDOW_FORMAT_RGB_565;
    Engine* engine = reinterpret_cast<Engine*>(app->userData);
    switch (cmd) {
        case APP_CMD_INIT_WINDOW:
            if (engine->AndroidApp()->window != NULL) {
				Xsize = ANativeWindow_getWidth(app->window);
				Ysize = ANativeWindow_getHeight(app->window);

				if(xscreendata == NULL){
					xscreendata = new unsigned char[Xsize * Ysize * 4];

LOGE("create pre amain");
					amain();
LOGE("create post amain");

					assetManager = app->activity->assetManager;

	                // save current format to format variable, and set
	                // display format to 565 to save time coping. normally
	                // 565 might be buggy ( if 565 works, 32 bit mostly like
	                // would work )				
	                format = ANativeWindow_getFormat(app->window);
				}
                ANativeWindow_setBuffersGeometry(app->window,
                              ANativeWindow_getWidth(app->window),
                              ANativeWindow_getHeight(app->window),
                              WINDOW_FORMAT_RGBX_8888	//WINDOW_FORMAT_RGB_565	//WINDOW_FORMAT_RGBX_8888	//WINDOW_FORMAT_RGB_565
                );
				ANativeActivity* activity = app->activity;
				goToFullscreenMode(activity);

                engine->PrepareDrawing();
                engine->StartAnimation(true);
                engine->UpdateDisplay();

//LOGE("create pre amain");
//				amain();
//LOGE("create post amain");
            }
            break;
        case APP_CMD_TERM_WINDOW:
            engine->StartAnimation(false);
            engine->TerminateDisplay();
            ANativeWindow_setBuffersGeometry(app->window,
                          ANativeWindow_getWidth(app->window),
                          ANativeWindow_getHeight(app->window),
                          format);

//            delete[] xscreendata;
//			xscreendata = NULL;
LOGE("terminate window");
            break;
        case APP_CMD_LOST_FOCUS:
            engine->StartAnimation(false);
            engine->UpdateDisplay();
            break;
		case APP_CMD_DESTROY: 
LOGI("terminate app\n");
//			delete[] xscreendata;
//			xscreendata = NULL;
			break; 
    }
}


// Android application glue entry function for us
extern "C" void android_main(struct android_app* state) {

    Engine engine(state);

    state->userData = reinterpret_cast<void*>(&engine);
    state->onAppCmd = ProcessAndroidCmd;
    state->onInputEvent = ProcessAndroidInput;


    // loop waiting for stuff to do.
    while (1) {
        // Read all pending events.
        int ident;
        int events;
        struct android_poll_source* source;

        // If not animating, we will block forever waiting for events.
        // If animating, we loop until all events are read, then continue
        // to draw the next frame of animation.
        while ((ident = ALooper_pollAll(engine.IsAnimating() ? 0 : -1, NULL, &events,
                (void**)&source)) >= 0) {

            // Process this event.
            if (source != NULL) {
                source->process(state, source);
            }

            // Check if we are exiting.
            if (state->destroyRequested != 0) {
                LOGI("Engine thread destroy requested!");
                engine.TerminateDisplay();
                return;
            }
        }

        if (engine.IsAnimating()) {
            engine.UpdateDisplay();
        }
    }
}


// Engine class implementations
bool Engine::PrepareDrawing(void) {
    ANativeWindow_Buffer buf;
    if (ANativeWindow_lock(app_->window, &buf, NULL) < 0) {
        LOGW("Unable to lock window buffer to create decoder");
        return false;
    }
    UpdateFrameBuffer(&buf, nullptr);
	
    ANativeWindow_unlockAndPost(app_->window);

    return true;
}


bool Engine::UpdateDisplay(void) {
    if (!app_->window) {
        assert(0);
        return false;
    }
    struct timespec curTime;
    clock_gettime(CLOCK_MONOTONIC, &curTime);
    if(
		curTime.tv_sec >= (frameStartTime_.tv_sec + (__kernel_time_t )kFRAME_DISPLAY_TIME)
	){
		is_int_refresh = 0;
	}else if (
		is_int_refresh && (
			curTime.tv_sec >= (smallFrameStartTime_.tv_sec + (__kernel_time_t )1) ||
			curTime.tv_nsec >= (smallFrameStartTime_.tv_nsec + 75000000L)
		)
	) {
		;
	}else{
        // current frame is displayed less than required duration
        return false;
    }
    uint8_t *frame = (uint8_t*)xscreendata;
    if (!frame)
        return false;

    ANativeWindow_Buffer buffer;
    if (ANativeWindow_lock(app_->window, &buffer, nullptr) < 0) {
        LOGE("Unable to lock window buffer");
        return false;
    }
	
    UpdateFrameBuffer(&buffer, frame);
	
    ANativeWindow_unlockAndPost(app_->window);

//	if(is_int_refresh == 0)
//		clock_gettime(CLOCK_MONOTONIC, &frameStartTime_);
//	else
		is_int_refresh = 0;
	
	clock_gettime(CLOCK_MONOTONIC, &frameStartTime_);
	clock_gettime(CLOCK_MONOTONIC, &smallFrameStartTime_);
	
    return true;
}


/*
 * UpdateFrameBuffer():
 *     Internal function to perform bits copying onto current frame buffer
 *     src:
 *        - if nullptr, blank it
 *        - otherwise,  copy to given buf
 *     assumption:
 *         src and bug MUST be in the same geometry format & layout
 */
void Engine::UpdateFrameBuffer(ANativeWindow_Buffer* buf, uint8_t* src) {
    // src is either null: to blank the screen
    //     or holding exact pixels with the same fmt [stride is the SAME]
    uint8_t *dst = reinterpret_cast<uint8_t*> (buf->bits);
    uint32_t bpp;
    int i, j;

LOGE("update fb fmt=%d, buf=%x", buf->format, dst);
    switch (buf->format) {
        case WINDOW_FORMAT_RGB_565:
            bpp = 2;
            break;
        case WINDOW_FORMAT_RGBA_8888:
        case WINDOW_FORMAT_RGBX_8888:
            bpp = 4;
            break;
        default:
            assert( 0 );
            return;
    }

//	if(is_int_refresh == 0){
		xb = 0;
		yb = 0;
		xe = Xsize; //buf->width;
		ye = Ysize; //buf->height;
//	}
	
    uint32_t stride, width;
    stride = buf->stride * bpp;
    width = xe * bpp;
	
    if (src) {
        for (int height = yb; height < ye; ++height) {
            for(i = xb * bpp, j = xb * 4; i < width; ){
				unsigned short r = src[j+2];
				unsigned short g = src[j+1];
				unsigned short b = src[j];
				
				switch (buf->format) {
					case WINDOW_FORMAT_RGB_565:
						*((unsigned short*)&dst[i]) = 
										((r & 31) << 11) +
										((g & 63) << 5) +
										(b & 31)
										;
 						break;
					case WINDOW_FORMAT_RGBA_8888:
					case WINDOW_FORMAT_RGBX_8888:
						dst[i+0] = (uint8_t)r;
						dst[i+1] = (uint8_t)g;
						dst[i+2] = (uint8_t)b;
//						dst[i+3] = src[j+3];
						break;
					default:
						assert( 0 );
						return;
				};
				j += 4;
				i += bpp;
            }
			
            dst += stride;
			src += Xsize * 4;
        }
    }
#if 0
	  else {
        for (auto height =0; height < buf->height; ++height) {
            for(i = 0; i < width; i++ /*+= bpp*/){
				if((int)(i/bpp) == height)
					dst[i] = 0xff;
				else
					dst[i] = 0;
            }
            //memset(dst, 0, width);
            dst += stride;
        }
    }
#endif
}












////////////////////////////////////////////////////////////
#if 0
int getAndroidApiLevel(ANativeActivity* activity)
{
    JNIEnv* lJNIEnv = activity->env;

    jclass versionClass = lJNIEnv->FindClass("android/os/Build$VERSION");
    if (versionClass == NULL)
        return 0;

    jfieldID sdkIntFieldID = lJNIEnv->GetStaticFieldID(versionClass, "SDK_INT", "I");
    if (sdkIntFieldID == NULL)
        return 0;
    
    jint sdkInt = 0;
    sdkInt = lJNIEnv->GetStaticIntField(versionClass, sdkIntFieldID);
    
    return sdkInt;
}
#endif


////////////////////////////////////////////////////////////
void goToFullscreenMode(ANativeActivity* activity)
{
    // Get the current Android API level.
//    int apiLevel = 24; //getAndroidApiLevel(activity);

    // Hide the status bar
    ANativeActivity_setWindowFlags(activity, AWINDOW_FLAG_FULLSCREEN,
        AWINDOW_FLAG_FULLSCREEN);

#if 0
    // Hide the navigation bar
    JavaVM* lJavaVM = activity->vm;
    JNIEnv* lJNIEnv = activity->env;

    jobject objectActivity = activity->clazz;
    jclass classActivity = lJNIEnv->GetObjectClass(objectActivity);

    jmethodID methodGetWindow = lJNIEnv->GetMethodID(classActivity, "getWindow", "()Landroid/view/Window;");
    jobject objectWindow = lJNIEnv->CallObjectMethod(objectActivity, methodGetWindow);

    jclass classWindow = lJNIEnv->FindClass("android/view/Window");
    jmethodID methodGetDecorView = lJNIEnv->GetMethodID(classWindow, "getDecorView", "()Landroid/view/View;");
    jobject objectDecorView = lJNIEnv->CallObjectMethod(objectWindow, methodGetDecorView);

    jclass classView = lJNIEnv->FindClass("android/view/View");

    // Default flags
    jint flags = 0;
    
    // API Level 14
    if (apiLevel >= 14)
    {
        jfieldID FieldSYSTEM_UI_FLAG_LOW_PROFILE = lJNIEnv->GetStaticFieldID(classView, "SYSTEM_UI_FLAG_LOW_PROFILE", "I");
        jint SYSTEM_UI_FLAG_LOW_PROFILE = lJNIEnv->GetStaticIntField(classView, FieldSYSTEM_UI_FLAG_LOW_PROFILE);
        flags |= SYSTEM_UI_FLAG_LOW_PROFILE;
    }

    // API Level 16
    if (apiLevel >= 16)
    {
        jfieldID FieldSYSTEM_UI_FLAG_FULLSCREEN = lJNIEnv->GetStaticFieldID(classView, "SYSTEM_UI_FLAG_FULLSCREEN", "I");
        jint SYSTEM_UI_FLAG_FULLSCREEN = lJNIEnv->GetStaticIntField(classView, FieldSYSTEM_UI_FLAG_FULLSCREEN);
        flags |= SYSTEM_UI_FLAG_FULLSCREEN;
    }

    // API Level 19
    if (apiLevel >= 19)
    {
        jfieldID FieldSYSTEM_UI_FLAG_IMMERSIVE_STICKY  = lJNIEnv->GetStaticFieldID(classView, "SYSTEM_UI_FLAG_IMMERSIVE_STICKY", "I");
        jint SYSTEM_UI_FLAG_IMMERSIVE_STICKY = lJNIEnv->GetStaticIntField(classView, FieldSYSTEM_UI_FLAG_IMMERSIVE_STICKY);
        flags |= SYSTEM_UI_FLAG_IMMERSIVE_STICKY;
    }

    jmethodID methodsetSystemUiVisibility = lJNIEnv->GetMethodID(classView, "setSystemUiVisibility", "(I)V");
    lJNIEnv->CallVoidMethod(objectDecorView, methodsetSystemUiVisibility, flags);
#endif
}

////////////////////////////////////////////////////////////






#if 0

////////////////////////////////////////////////////////////
static void onStart(ANativeActivity* activity)
{
}


////////////////////////////////////////////////////////////
static void onResume(ANativeActivity* activity)
{
    // Retrieve our activity states from the activity instance
//    sf::priv::ActivityStates* states = sf::priv::retrieveStates(activity);
//    sf::Lock lock(states->mutex);

//    if (states->fullscreen)
        goToFullscreenMode(activity);

    // Send an event to warn people the activity has been resumed
//    sf::Event event;
//    event.type = sf::Event::MouseEntered;

//    states->forwardEvent(event);
}


////////////////////////////////////////////////////////////
static void onPause(ANativeActivity* activity)
{
/*
    // Retrieve our activity states from the activity instance
    sf::priv::ActivityStates* states = sf::priv::retrieveStates(activity);
    sf::Lock lock(states->mutex);

    // Send an event to warn people the activity has been paused
    sf::Event event;
    event.type = sf::Event::MouseLeft;

    states->forwardEvent(event);
*/
}


////////////////////////////////////////////////////////////
static void onStop(ANativeActivity* activity)
{
}


////////////////////////////////////////////////////////////
static void onDestroy(ANativeActivity* activity)
{
#if 0
    // Retrieve our activity states from the activity instance
    sf::priv::ActivityStates* states = sf::priv::retrieveStates(activity);

    // Send an event to warn people the activity is being destroyed
    {
        sf::Lock lock(states->mutex);

        // If the main thread hasn't yet finished, send the event and wait for
        // it to finish.
        if (!states->mainOver)
        {
            sf::Event event;
            event.type = sf::Event::Closed;

            states->forwardEvent(event);
        }
    }

    // Wait for the main thread to be terminated
    states->mutex.lock();

    while (!states->terminated)
    {
        states->mutex.unlock();
        sf::sleep(sf::milliseconds(20));
        states->mutex.lock();
    }

    states->mutex.unlock();

    // Terminate EGL display
    eglTerminate(states->display);

    // Delete our allocated states
    delete states;

    // Reset the activity pointer for all modules
    sf::priv::getActivity(NULL, true);
#endif

    // The application should now terminate
}


////////////////////////////////////////////////////////////
static void onNativeWindowCreated(ANativeActivity* activity, ANativeWindow* window)
{
#if 0
    sf::priv::ActivityStates* states = sf::priv::retrieveStates(activity);
    sf::Lock lock(states->mutex);

    // Update the activity states
    states->window = window;

    // Notify SFML mechanism
    sf::Event event;
    event.type = sf::Event::GainedFocus;
    states->forwardEvent(event);

    // Wait for the event to be taken into account by SFML
    states->updated = false;
    while(!states->updated)
    {
        states->mutex.unlock();
        sf::sleep(sf::milliseconds(10));
        states->mutex.lock();
    }
#endif
}


////////////////////////////////////////////////////////////
static void onNativeWindowDestroyed(ANativeActivity* activity, ANativeWindow* window)
{
#if 0
    sf::priv::ActivityStates* states = sf::priv::retrieveStates(activity);
    sf::Lock lock(states->mutex);

    // Update the activity states
    states->window = NULL;

    // Notify SFML mechanism
    sf::Event event;
    event.type = sf::Event::LostFocus;
    states->forwardEvent(event);

    // Wait for the event to be taken into account by SFML
    states->updated = false;
    while(!states->updated)
    {
        states->mutex.unlock();
        sf::sleep(sf::milliseconds(10));
        states->mutex.lock();
    }
#endif
}


////////////////////////////////////////////////////////////
static void onNativeWindowRedrawNeeded(ANativeActivity* activity, ANativeWindow* window)
{
}


////////////////////////////////////////////////////////////
static void onNativeWindowResized(ANativeActivity* activity, ANativeWindow* window)
{
}


////////////////////////////////////////////////////////////
static void onInputQueueCreated(ANativeActivity* activity, AInputQueue* queue)
{
#if 0
    // Retrieve our activity states from the activity instance
    sf::priv::ActivityStates* states = sf::priv::retrieveStates(activity);

    // Attach the input queue
    {
        sf::Lock lock(states->mutex);

        AInputQueue_attachLooper(queue, states->looper, 1, states->processEvent, NULL);
        states->inputQueue = queue;
    }
#endif
}


////////////////////////////////////////////////////////////
static void onInputQueueDestroyed(ANativeActivity* activity, AInputQueue* queue)
{
#if 0
    // Retrieve our activity states from the activity instance
    sf::priv::ActivityStates* states = sf::priv::retrieveStates(activity);

    // Detach the input queue
    {
        sf::Lock lock(states->mutex);

        states->inputQueue = NULL;
        AInputQueue_detachLooper(queue);
    }
#endif
}


////////////////////////////////////////////////////////////
static void onWindowFocusChanged(ANativeActivity* activity, int focused)
{
}


////////////////////////////////////////////////////////////
static void onContentRectChanged(ANativeActivity* activity, const ARect* rect)
{
#if 0
    // Retrieve our activity states from the activity instance
    sf::priv::ActivityStates* states = sf::priv::retrieveStates(activity);
    sf::Lock lock(states->mutex);

    // Make sure the window still exists before we access the dimensions on it
    if (states->window != NULL) {
        // Send an event to warn people about the window move/resize
        sf::Event event;
        event.type = sf::Event::Resized;
        event.size.width = ANativeWindow_getWidth(states->window);
        event.size.height = ANativeWindow_getHeight(states->window);

        states->forwardEvent(event);
    }
#endif
}


////////////////////////////////////////////////////////////
static void onConfigurationChanged(ANativeActivity* activity)
{
}


////////////////////////////////////////////////////////////
static void* onSaveInstanceState(ANativeActivity* activity, size_t* outLen)
{
    *outLen = 0;

    return NULL;
}


////////////////////////////////////////////////////////////
static void onLowMemory(ANativeActivity* activity)
{
}


////////////////////////////////////////////////////////////
void ANativeActivity_onCreate(ANativeActivity* activity, void* savedState, size_t savedStateSize)
{
#if 0
    // Create an activity states (will keep us in the know, about events we care)
    sf::priv::ActivityStates* states = NULL;
    states = new sf::priv::ActivityStates;

    // Initialize the states value
    states->activity   = NULL;
    states->window     = NULL;
    states->looper     = NULL;
    states->inputQueue = NULL;
    states->config     = NULL;

    for (unsigned int i = 0; i < sf::Mouse::ButtonCount; i++)
        states->isButtonPressed[i] = false;

    states->display = eglGetDisplay(EGL_DEFAULT_DISPLAY);

    if (savedState != NULL)
    {
        states->savedState = malloc(savedStateSize);
        states->savedStateSize = savedStateSize;
        memcpy(states->savedState, savedState, savedStateSize);
    }

    states->mainOver = false;

    states->initialized = false;
    states->terminated = false;

    // Share it across the SFML modules
    sf::priv::getActivity(states, true);
#endif

    // These functions will update the activity states and therefore, will allow
    // SFML to be kept in the know
    activity->callbacks->onStart   = onStart;
    activity->callbacks->onResume  = onResume;
    activity->callbacks->onPause   = onPause;
    activity->callbacks->onStop    = onStop;
    activity->callbacks->onDestroy = onDestroy;

    activity->callbacks->onNativeWindowCreated = onNativeWindowCreated;
    activity->callbacks->onNativeWindowDestroyed = onNativeWindowDestroyed;
    activity->callbacks->onNativeWindowRedrawNeeded = onNativeWindowRedrawNeeded;
    activity->callbacks->onNativeWindowResized = onNativeWindowResized;

    activity->callbacks->onInputQueueCreated = onInputQueueCreated;
    activity->callbacks->onInputQueueDestroyed = onInputQueueDestroyed;

    activity->callbacks->onWindowFocusChanged = onWindowFocusChanged;
    activity->callbacks->onContentRectChanged = onContentRectChanged;
    activity->callbacks->onConfigurationChanged = onConfigurationChanged;

    activity->callbacks->onSaveInstanceState = onSaveInstanceState;
    activity->callbacks->onLowMemory = onLowMemory;

    // Share this activity with the callback functions
//    states->activity = activity;

    // Keep the screen turned on and bright
    ANativeActivity_setWindowFlags(activity, AWINDOW_FLAG_KEEP_SCREEN_ON,
        AWINDOW_FLAG_KEEP_SCREEN_ON);

    // Initialize the display
//    eglInitialize(states->display, NULL, NULL);

//    getScreenSizeInPixels(activity, &states->screenSize.x, &states->screenSize.y);

    // Redirect error messages to logcat
  //  sf::err().rdbuf(&states->logcat);

    // Launch the main thread
//    sf::Thread* thread = new sf::Thread(sf::priv::main, states);
//    thread->launch();

    // Wait for the main thread to be initialized
//    states->mutex.lock();

//    while (!states->initialized)
//    {
//        states->mutex.unlock();
//        sf::sleep(sf::milliseconds(20));
//        states->mutex.lock();
//    }

//    states->mutex.unlock();

    // Share this state with the callback functions
//    activity->instance = states;
}

#endif



