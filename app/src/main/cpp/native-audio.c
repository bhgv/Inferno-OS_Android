/*
 * Copyright (C) 2010 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */


#include <stdlib.h>

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#include <assert.h>
//#include <jni.h>
#include <string.h>
#include <pthread.h>


// for __android_log_print(ANDROID_LOG_INFO, "YourApp", "formatted message");
// #include <android/log.h>

// for native audio
#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>

// for native asset manager
#include <sys/types.h>
#include <android/asset_manager.h>
//#include <android/asset_manager_jni.h>


//#define __USE_C99_MATH
#include <stdbool.h>

#define TRUE true
#define FALSE false

#include <android/log.h>


#define  LOG_TAG    "inferno AUD"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGW(...)  __android_log_print(ANDROID_LOG_WARN,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)


// engine interfaces
static SLObjectItf engineObject = NULL;
static SLEngineItf engineEngine;

// output mix interfaces
static SLObjectItf outputMixObject = NULL;
static SLEnvironmentalReverbItf outputMixEnvironmentalReverb = NULL;

// buffer queue player interfaces
static SLObjectItf bqPlayerObject = NULL;
static SLPlayItf bqPlayerPlay;
static SLAndroidSimpleBufferQueueItf bqPlayerBufferQueue;
static SLEffectSendItf bqPlayerEffectSend;
static SLMuteSoloItf bqPlayerMuteSolo;
static SLVolumeItf bqPlayerVolume;
static SLmilliHertz bqPlayerSampleRate = 0;
static int   bqPlayerBufSize = 0;
// a mutext to guard against re-entrance to record & playback
// as well as make recording and playing back to be mutually exclusive
// this is to avoid crash at situations like:
//    recording is in session [not finished]
//    user presses record button and another recording coming in
// The action: when recording/playing back is not finished, ignore the new request
static pthread_mutex_t  audioEngineLock = PTHREAD_MUTEX_INITIALIZER;

// aux effect on the output mix, used by the buffer queue player
static const SLEnvironmentalReverbSettings reverbSettings =
    SL_I3DL2_ENVIRONMENT_PRESET_STONECORRIDOR;

// URI player interfaces
static SLObjectItf uriPlayerObject = NULL;
static SLPlayItf uriPlayerPlay;
static SLSeekItf uriPlayerSeek;
static SLMuteSoloItf uriPlayerMuteSolo;
static SLVolumeItf uriPlayerVolume;

// file descriptor player interfaces
static SLObjectItf fdPlayerObject = NULL;
static SLPlayItf fdPlayerPlay;
static SLSeekItf fdPlayerSeek;
static SLMuteSoloItf fdPlayerMuteSolo;
static SLVolumeItf fdPlayerVolume;

// recorder interfaces
static SLObjectItf recorderObject = NULL;
static SLRecordItf recorderRecord;
static SLAndroidSimpleBufferQueueItf recorderBufferQueue;

// 1 second of recorded audio at 44.1 kHz mono, 16-bit signed little endian
#define RECORDER_FRAMES (44100 * 1)
static short recorderBuffer1[RECORDER_FRAMES];
static short recorderBuffer2[RECORDER_FRAMES];
static short** recorderBuffers[] = {
	recorderBuffer1,
	recorderBuffer2
};
static int curRecBuf = 0;
static unsigned recorderSize = 0;

// pointer and size of the next player buffer to enqueue, and number of remaining buffers
static short *nextBuffers[2];
static int curBuf = 0;
static unsigned nextSizes[2];

static int is_play = 0;
static int is_rec = 0;

static int glob_fd = -1;


#if 0
// synthesize a mono sawtooth wave and place it into a buffer (called automatically on load)
__attribute__((constructor)) static void onDlOpen(void)
{
/*
    unsigned i;
    for (i = 0; i < SAWTOOTH_FRAMES; ++i) {
        sawtoothBuffer[i] = 32768 - ((i % 100) * 660);
    }
*/
}
#endif



// this callback handler is called every time a buffer finishes playing
void bqPlayerCallback(SLAndroidSimpleBufferQueueItf bq, void *context)
{
	int curBuf_ = curBuf ^ 1;
	
    assert(bq == bqPlayerBufferQueue);
    assert(NULL == context);

    // for streaming playback, replace this test by logic to find and fill the next buffer
    if (
		nextBuffers[curBuf_] != NULL 
		&& nextSizes[curBuf_] != 0
	) 
	{
        SLresult result;
		
        // enqueue another buffer
//LOGI("%s: %d", __func__, __LINE__);
        result = (*bqPlayerBufferQueue)->Enqueue(bqPlayerBufferQueue, nextBuffers[curBuf_], nextSizes[curBuf_]);
        // the most likely other result is SL_RESULT_BUFFER_INSUFFICIENT,
        // which for this code example would indicate a programming error

		if(nextBuffers[curBuf])
			free(nextBuffers[curBuf]);
		nextBuffers[curBuf] = NULL;

		nextSizes[curBuf] = 0;

		curBuf = curBuf_;

		is_play = TRUE;
		
//        if (SL_RESULT_SUCCESS != result) {
//            pthread_mutex_unlock(&audioEngineLock);
//        }
        (void)result;
    } else {
		if(nextBuffers[curBuf])
			free(nextBuffers[curBuf]);
		nextBuffers[curBuf] = NULL;

		nextSizes[curBuf] = 0;

		curBuf = curBuf_;
		
		if(nextBuffers[curBuf])
			free(nextBuffers[curBuf]);
		nextBuffers[curBuf] = NULL;

		nextSizes[curBuf] = 0;

		is_play = FALSE;

//LOGI("%s: %d", __func__, __LINE__);
//        pthread_mutex_unlock(&audioEngineLock);
    }
}


// this callback handler is called every time a buffer finishes recording
void bqRecorderCallback(SLAndroidSimpleBufferQueueItf bq, void *context)
{
    assert(bq == recorderBufferQueue);
    assert(NULL == context);
    // for streaming recording, here we would call Enqueue to give recorder the next buffer to fill
    // but instead, this is a one-time buffer so we stop recording
    SLresult result;

	curRecBuf ^= 1;

    // enqueue an empty buffer to be filled by the recorder
    // (for streaming recording, we would enqueue at least 2 empty buffers to start things off)
    result = (*recorderBufferQueue)->Enqueue(recorderBufferQueue, recorderBuffers[curRecBuf],
            RECORDER_FRAMES * sizeof(short));
    // the most likely other result is SL_RESULT_BUFFER_INSUFFICIENT,
    // which for this code example would indicate a programming error
    assert(SL_RESULT_SUCCESS == result);
    (void)result;

/*
    result = (*recorderRecord)->SetRecordState(recorderRecord, SL_RECORDSTATE_STOPPED);
*/
    if (SL_RESULT_SUCCESS == result) {
        recorderSize = RECORDER_FRAMES * sizeof(short);
    }else{
    	recorderSize = 0;
		is_rec = FALSE;
    }
//    pthread_mutex_unlock(&audioEngineLock);
}


// create the engine and output mix objects
//void Java_com_example_nativeaudio_NativeAudio_createEngine(JNIEnv* env, jclass clazz)
void NativeAudio_createEngine()
{
    SLresult result;

    // create engine
    result = slCreateEngine(&engineObject, 0, NULL, 0, NULL, NULL);
    assert(SL_RESULT_SUCCESS == result);
    (void)result;

    // realize the engine
    result = (*engineObject)->Realize(engineObject, SL_BOOLEAN_FALSE);
    assert(SL_RESULT_SUCCESS == result);
    (void)result;

    // get the engine interface, which is needed in order to create other objects
    result = (*engineObject)->GetInterface(engineObject, SL_IID_ENGINE, &engineEngine);
    assert(SL_RESULT_SUCCESS == result);
    (void)result;

    // create output mix, with environmental reverb specified as a non-required interface
    const SLInterfaceID ids[1] = {SL_IID_ENVIRONMENTALREVERB};
    const SLboolean req[1] = {SL_BOOLEAN_FALSE};
    result = (*engineEngine)->CreateOutputMix(engineEngine, &outputMixObject, 1, ids, req);
    assert(SL_RESULT_SUCCESS == result);
    (void)result;

    // realize the output mix
    result = (*outputMixObject)->Realize(outputMixObject, SL_BOOLEAN_FALSE);
    assert(SL_RESULT_SUCCESS == result);
    (void)result;

    // get the environmental reverb interface
    // this could fail if the environmental reverb effect is not available,
    // either because the feature is not present, excessive CPU load, or
    // the required MODIFY_AUDIO_SETTINGS permission was not requested and granted
    result = (*outputMixObject)->GetInterface(outputMixObject, SL_IID_ENVIRONMENTALREVERB,
            &outputMixEnvironmentalReverb);
    if (SL_RESULT_SUCCESS == result) {
        result = (*outputMixEnvironmentalReverb)->SetEnvironmentalReverbProperties(
                outputMixEnvironmentalReverb, &reverbSettings);
        (void)result;
    }
    // ignore unsuccessful result codes for environmental reverb, as it is optional for this example

}


// create buffer queue audio player
//void Java_com_example_nativeaudio_NativeAudio_createBufferQueueAudioPlayer(/*JNIEnv* env,
//        jclass clazz,*/ int sampleRate, int bufSize)
void NativeAudio_createBufferQueueAudioPlayer(int sampleRate, int bufSize)
{
    SLresult result;

//	sampleRate = SL_SAMPLINGRATE_44_1 / 1000;
//	bufSize = 512;

	nextBuffers[0] = NULL;
	nextBuffers[1] = NULL;

	nextSizes[0] = 0;
	nextSizes[1] = 0;

	curBuf = 0;

	is_play = FALSE;
	
    if (sampleRate >= 0 && bufSize >= 0 ) {
        bqPlayerSampleRate = sampleRate * 1000;
        /*
         * device native buffer size is another factor to minimize audio latency, not used in this
         * sample: we only play one giant buffer here
         */
        bqPlayerBufSize = bufSize;
    }
//LOGI("cr buff 1: sampleRate=%d, SL_SAMPLINGRATE_44_1=%d", sampleRate, SL_SAMPLINGRATE_44_1);
    // configure audio source
    SLDataLocator_AndroidSimpleBufferQueue loc_bufq = {SL_DATALOCATOR_ANDROIDSIMPLEBUFFERQUEUE, 2};
    SLDataFormat_PCM format_pcm = {SL_DATAFORMAT_PCM, 
/*
		1, 
		SL_SAMPLINGRATE_8,
        SL_PCMSAMPLEFORMAT_FIXED_16, 
        SL_PCMSAMPLEFORMAT_FIXED_16,
        SL_SPEAKER_FRONT_CENTER, 
        SL_BYTEORDER_LITTLEENDIAN
*/
	    2,
	    SL_SAMPLINGRATE_44_1,
	    SL_PCMSAMPLEFORMAT_FIXED_16,
	    SL_PCMSAMPLEFORMAT_FIXED_16,
	    SL_SPEAKER_FRONT_LEFT | SL_SPEAKER_FRONT_RIGHT,
	    SL_BYTEORDER_LITTLEENDIAN
	};
    /*
     * Enable Fast Audio when possible:  once we set the same rate to be the native, fast audio path
     * will be triggered
     */
    if(bqPlayerSampleRate) {
        format_pcm.samplesPerSec = bqPlayerSampleRate;       //sample rate in mili second
    }
    SLDataSource audioSrc = {&loc_bufq, &format_pcm};

    // configure audio sink
    SLDataLocator_OutputMix loc_outmix = {SL_DATALOCATOR_OUTPUTMIX, outputMixObject};
    SLDataSink audioSnk = {&loc_outmix, NULL};

    /*
     * create audio player:
     *     fast audio does not support when SL_IID_EFFECTSEND is required, skip it
     *     for fast audio case
     */
    const SLInterfaceID ids[3] = {SL_IID_BUFFERQUEUE, SL_IID_VOLUME, SL_IID_EFFECTSEND,
                                    /*SL_IID_MUTESOLO,*/};
    const SLboolean req[3] = {SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE,
                                   /*SL_BOOLEAN_TRUE,*/ };

    result = (*engineEngine)->CreateAudioPlayer(engineEngine, &bqPlayerObject, &audioSrc, &audioSnk,
            bqPlayerSampleRate? 2 : 3, ids, req);
    assert(SL_RESULT_SUCCESS == result);
    (void)result;

    // realize the player
    result = (*bqPlayerObject)->Realize(bqPlayerObject, SL_BOOLEAN_FALSE);
    assert(SL_RESULT_SUCCESS == result);
    (void)result;

    // get the play interface
    result = (*bqPlayerObject)->GetInterface(bqPlayerObject, SL_IID_PLAY, &bqPlayerPlay);
    assert(SL_RESULT_SUCCESS == result);
    (void)result;

    // get the buffer queue interface
    result = (*bqPlayerObject)->GetInterface(bqPlayerObject, SL_IID_BUFFERQUEUE,
            &bqPlayerBufferQueue);
    assert(SL_RESULT_SUCCESS == result);
    (void)result;

    // register callback on the buffer queue
    result = (*bqPlayerBufferQueue)->RegisterCallback(bqPlayerBufferQueue, bqPlayerCallback, NULL);
    assert(SL_RESULT_SUCCESS == result);
    (void)result;

    // get the effect send interface
    bqPlayerEffectSend = NULL;
    if( 0 == bqPlayerSampleRate) {
        result = (*bqPlayerObject)->GetInterface(bqPlayerObject, SL_IID_EFFECTSEND,
                                                 &bqPlayerEffectSend);
        assert(SL_RESULT_SUCCESS == result);
        (void)result;
    }

#if 0   // mute/solo is not supported for sources that are known to be mono, as this is
    // get the mute/solo interface
    result = (*bqPlayerObject)->GetInterface(bqPlayerObject, SL_IID_MUTESOLO, &bqPlayerMuteSolo);
    assert(SL_RESULT_SUCCESS == result);
    (void)result;
#endif

    // get the volume interface
    result = (*bqPlayerObject)->GetInterface(bqPlayerObject, SL_IID_VOLUME, &bqPlayerVolume);
    assert(SL_RESULT_SUCCESS == result);
    (void)result;

    // set the player's state to playing
    result = (*bqPlayerPlay)->SetPlayState(bqPlayerPlay, SL_PLAYSTATE_PLAYING);
    assert(SL_RESULT_SUCCESS == result);
    (void)result;
}


// create URI audio player
//jboolean Java_com_example_nativeaudio_NativeAudio_createUriAudioPlayer(JNIEnv* env, jclass clazz,
//		jstring uri)
bool NativeAudio_createUriAudioPlayer(char *uri)
{
    SLresult result;

    // convert Java string to UTF-8
    const char *utf8 = uri; //(*env)->GetStringUTFChars(env, uri, NULL);
    assert(NULL != utf8);

    // configure audio source
    // (requires the INTERNET permission depending on the uri parameter)
    SLDataLocator_URI loc_uri = {SL_DATALOCATOR_URI, (SLchar *) utf8};
    SLDataFormat_MIME format_mime = {SL_DATAFORMAT_MIME, NULL, SL_CONTAINERTYPE_UNSPECIFIED};
    SLDataSource audioSrc = {&loc_uri, &format_mime};

    // configure audio sink
    SLDataLocator_OutputMix loc_outmix = {SL_DATALOCATOR_OUTPUTMIX, outputMixObject};
    SLDataSink audioSnk = {&loc_outmix, NULL};

    // create audio player
    const SLInterfaceID ids[3] = {SL_IID_SEEK, SL_IID_MUTESOLO, SL_IID_VOLUME};
    const SLboolean req[3] = {SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE};
    result = (*engineEngine)->CreateAudioPlayer(engineEngine, &uriPlayerObject, &audioSrc,
            &audioSnk, 3, ids, req);
    // note that an invalid URI is not detected here, but during prepare/prefetch on Android,
    // or possibly during Realize on other platforms
    assert(SL_RESULT_SUCCESS == result);
    (void)result;

//    // release the Java string and UTF-8
//    (*env)->ReleaseStringUTFChars(env, uri, utf8);

    // realize the player
    result = (*uriPlayerObject)->Realize(uriPlayerObject, SL_BOOLEAN_FALSE);
    // this will always succeed on Android, but we check result for portability to other platforms
    if (SL_RESULT_SUCCESS != result) {
        (*uriPlayerObject)->Destroy(uriPlayerObject);
        uriPlayerObject = NULL;
        return FALSE;
    }

    // get the play interface
    result = (*uriPlayerObject)->GetInterface(uriPlayerObject, SL_IID_PLAY, &uriPlayerPlay);
    assert(SL_RESULT_SUCCESS == result);
    (void)result;

    // get the seek interface
    result = (*uriPlayerObject)->GetInterface(uriPlayerObject, SL_IID_SEEK, &uriPlayerSeek);
    assert(SL_RESULT_SUCCESS == result);
    (void)result;

    // get the mute/solo interface
    result = (*uriPlayerObject)->GetInterface(uriPlayerObject, SL_IID_MUTESOLO, &uriPlayerMuteSolo);
    assert(SL_RESULT_SUCCESS == result);
    (void)result;

    // get the volume interface
    result = (*uriPlayerObject)->GetInterface(uriPlayerObject, SL_IID_VOLUME, &uriPlayerVolume);
    assert(SL_RESULT_SUCCESS == result);
    (void)result;

    return TRUE;
}


// set the playing state for the URI audio player
// to PLAYING (true) or PAUSED (false)
//void Java_com_example_nativeaudio_NativeAudio_setPlayingUriAudioPlayer(JNIEnv* env,
//        jclass clazz, jboolean isPlaying)
void NativeAudio_setPlayingUriAudioPlayer(bool isPlaying)
{
    SLresult result;

    // make sure the URI audio player was created
    if (NULL != uriPlayerPlay) {

        // set the player's state
        result = (*uriPlayerPlay)->SetPlayState(uriPlayerPlay, isPlaying ?
            SL_PLAYSTATE_PLAYING : SL_PLAYSTATE_PAUSED);
        assert(SL_RESULT_SUCCESS == result);
        (void)result;
    }
}


// set the whole file looping state for the URI audio player
//void Java_com_example_nativeaudio_NativeAudio_setLoopingUriAudioPlayer(JNIEnv* env,
//        jclass clazz, jboolean isLooping)
void NativeAudio_setLoopingUriAudioPlayer(bool isLooping)
{
    SLresult result;

    // make sure the URI audio player was created
    if (NULL != uriPlayerSeek) {

        // set the looping state
        result = (*uriPlayerSeek)->SetLoop(uriPlayerSeek, (SLboolean) isLooping, 0,
                SL_TIME_UNKNOWN);
        assert(SL_RESULT_SUCCESS == result);
        (void)result;
    }
}


// expose the mute/solo APIs to Java for one of the 3 players

static SLMuteSoloItf getMuteSolo()
{
    if (uriPlayerMuteSolo != NULL)
        return uriPlayerMuteSolo;
    else if (fdPlayerMuteSolo != NULL)
        return fdPlayerMuteSolo;
    else
        return bqPlayerMuteSolo;
}


//void Java_com_example_nativeaudio_NativeAudio_setChannelMuteUriAudioPlayer(JNIEnv* env,
//        jclass clazz, jint chan, jboolean mute)
void NativeAudio_setChannelMuteUriAudioPlayer(int chan, bool mute)
{
    SLresult result;
    SLMuteSoloItf muteSoloItf = getMuteSolo();
    if (NULL != muteSoloItf) {
        result = (*muteSoloItf)->SetChannelMute(muteSoloItf, chan, mute);
        assert(SL_RESULT_SUCCESS == result);
        (void)result;
    }
}


//void Java_com_example_nativeaudio_NativeAudio_setChannelSoloUriAudioPlayer(JNIEnv* env,
//        jclass clazz, jint chan, jboolean solo)
void NativeAudio_setChannelSoloUriAudioPlayer(int chan, bool solo)
{
    SLresult result;
    SLMuteSoloItf muteSoloItf = getMuteSolo();
    if (NULL != muteSoloItf) {
        result = (*muteSoloItf)->SetChannelSolo(muteSoloItf, chan, solo);
        assert(SL_RESULT_SUCCESS == result);
        (void)result;
    }
}


//int Java_com_example_nativeaudio_NativeAudio_getNumChannelsUriAudioPlayer(JNIEnv* env, jclass clazz)
int NativeAudio_getNumChannelsUriAudioPlayer()
{
    SLuint8 numChannels;
    SLresult result;
    SLMuteSoloItf muteSoloItf = getMuteSolo();
    if (NULL != muteSoloItf) {
        result = (*muteSoloItf)->GetNumChannels(muteSoloItf, &numChannels);
        if (SL_RESULT_PRECONDITIONS_VIOLATED == result) {
            // channel count is not yet known
            numChannels = 0;
        } else {
            assert(SL_RESULT_SUCCESS == result);
        }
    } else {
        numChannels = 0;
    }
    return numChannels;
}


// expose the volume APIs to Java for one of the 3 players

static SLVolumeItf getVolume()
{
    if (uriPlayerVolume != NULL)
        return uriPlayerVolume;
    else if (fdPlayerVolume != NULL)
        return fdPlayerVolume;
    else
        return bqPlayerVolume;
}


//void Java_com_example_nativeaudio_NativeAudio_setVolumeUriAudioPlayer(JNIEnv* env, jclass clazz,
//        jint millibel)
void NativeAudio_setVolumeUriAudioPlayer(int millibel)
{
    SLresult result;
    SLVolumeItf volumeItf = getVolume();
    if (NULL != volumeItf) {
        result = (*volumeItf)->SetVolumeLevel(volumeItf, millibel);
        assert(SL_RESULT_SUCCESS == result);
        (void)result;
    }
}


//void Java_com_example_nativeaudio_NativeAudio_setMuteUriAudioPlayer(JNIEnv* env, jclass clazz,
//        jboolean mute)
void NativeAudio_setMuteUriAudioPlayer(bool mute)
{
    SLresult result;
    SLVolumeItf volumeItf = getVolume();
    if (NULL != volumeItf) {
        result = (*volumeItf)->SetMute(volumeItf, mute);
        assert(SL_RESULT_SUCCESS == result);
        (void)result;
    }
}


//void Java_com_example_nativeaudio_NativeAudio_enableStereoPositionUriAudioPlayer(JNIEnv* env,
//        jclass clazz, jboolean enable)
void NativeAudio_enableStereoPositionUriAudioPlayer(bool enable)
{
    SLresult result;
    SLVolumeItf volumeItf = getVolume();
    if (NULL != volumeItf) {
        result = (*volumeItf)->EnableStereoPosition(volumeItf, enable);
        assert(SL_RESULT_SUCCESS == result);
        (void)result;
    }
}


//void Java_com_example_nativeaudio_NativeAudio_setStereoPositionUriAudioPlayer(JNIEnv* env,
//        jclass clazz, jint permille)
void NativeAudio_setStereoPositionUriAudioPlayer(int permille)
{
    SLresult result;
    SLVolumeItf volumeItf = getVolume();
    if (NULL != volumeItf) {
        result = (*volumeItf)->SetStereoPosition(volumeItf, permille);
        assert(SL_RESULT_SUCCESS == result);
        (void)result;
    }
}


// enable reverb on the buffer queue player
//jboolean Java_com_example_nativeaudio_NativeAudio_enableReverb(JNIEnv* env, jclass clazz,
//        jboolean enabled)
bool NativeAudio_enableReverb(bool enabled)
{
    SLresult result;

    // we might not have been able to add environmental reverb to the output mix
    if (NULL == outputMixEnvironmentalReverb) {
        return FALSE;
    }

    if(bqPlayerSampleRate) {
        /*
         * we are in fast audio, reverb is not supported.
         */
        return FALSE;
    }
    result = (*bqPlayerEffectSend)->EnableEffectSend(bqPlayerEffectSend,
            outputMixEnvironmentalReverb, (SLboolean) enabled, (SLmillibel) 0);
    // and even if environmental reverb was present, it might no longer be available
    if (SL_RESULT_SUCCESS != result) {
        return FALSE;
    }

    return TRUE;
}



#define VVV_MAIN

// select the desired clip and play count, and enqueue the first buffer if idle
//jboolean Java_com_example_nativeaudio_NativeAudio_selectClip(JNIEnv* env, jclass clazz, jint which,
//        jint count)
bool NativeAudio_setBufClip(int *nbuf, char* buf, int buf_size)
{
	int curBuf_ = curBuf ^ 1;

    if (
		buf_size == 0 
		|| buf == NULL 
		|| (is_play && *nbuf == curBuf_) 
//		|| pthread_mutex_trylock(&audioEngineLock)
	) {
//LOGI("%s: %d buf_size=%d, buf=%x, is_play=%d, *nbuf=%d, curBuf=%d", __func__, __LINE__, 
//														buf_size, buf, is_play, *nbuf, curBuf);
        // If we could not acquire audio engine lock, reject this request and client should re-try
        return FALSE;
    }
	
//LOGI("set buf %d buf=%x, sz=%d", __LINE__, buf, buf_size);
	if(nextBuffers[curBuf_])
		free(nextBuffers[curBuf_]);
	nextBuffers[curBuf_] = NULL;
	
//LOGI("%s: %d", __func__, __LINE__);

	nextBuffers[curBuf_] = (short*)malloc(buf_size + 4);
	
//LOGI("%s: %d nextBuffer=%x, buf=%x, buf_size=%d, curBuf_=%d", __func__, __LINE__, nextBuffers[curBuf_], buf, buf_size, curBuf_);
	memcpy(nextBuffers[curBuf_], buf, buf_size);

	nextSizes[curBuf_] = buf_size;

	*nbuf = curBuf_;
	
//LOGI("set buf %d nextSize=%d", __LINE__, nextSizes[curBuf_]);
	
    if ( !is_play) {
        // here we only enqueue one buffer because it is a long clip,
        // but for streaming playback we would typically enqueue at least 2 buffers to start
        SLresult result;
        result = (*bqPlayerBufferQueue)->Enqueue(bqPlayerBufferQueue, nextBuffers[curBuf_], nextSizes[curBuf_]);
//LOGI("set buf %d enc_res=%d", __LINE__, result);
        if (SL_RESULT_SUCCESS != result) {
			free(nextBuffers[curBuf_]);

			nextBuffers[curBuf_] = NULL;
		
			nextSizes[curBuf_] = 0;

			is_play = FALSE;
			
//            pthread_mutex_unlock(&audioEngineLock);
            return FALSE;
        }
		curBuf = curBuf_;
		
		is_play = TRUE;
    } 
//	else {
//        pthread_mutex_unlock(&audioEngineLock);
//    }

//	pthread_mutex_unlock(&audioEngineLock);

    return TRUE;
}

#define AAA_MAIN


// create asset audio player
//jboolean Java_com_example_nativeaudio_NativeAudio_createAssetAudioPlayer(JNIEnv* env, jclass clazz,
//        jobject assetManager, jstring filename)
bool NativeAudio_createFileAudioPlayer(char *filename)
{
    SLresult result;

    // convert Java string to UTF-8
//    const char *utf8 = (*env)->GetStringUTFChars(env, filename, NULL);
//    assert(NULL != utf8);

    // use asset manager to open asset by filename
//    AAssetManager* mgr = AAssetManager_fromJava(env, assetManager);
//    assert(NULL != mgr);
//    AAsset* asset = AAssetManager_open(mgr, utf8, AASSET_MODE_UNKNOWN);

    // release the Java string and UTF-8
//    (*env)->ReleaseStringUTFChars(env, filename, utf8);

    // the asset might not be found
//    if (NULL == asset) {
//        return JNI_FALSE;
//    }

	if(glob_fd != -1)
		close(glob_fd);
	glob_fd = -1;
	
    // open asset as file descriptor
    off_t start, length;
    int fd = open(filename, O_RDONLY); //AAsset_openFileDescriptor(asset, &start, &length);
//LOGI("%s: %d fd=%d", __func__, __LINE__, fd);
    if(fd <= 0)
		return FALSE;
	
    assert(0 <= fd);
//    AAsset_close(asset);

	//start = 0;
	
	length = lseek(fd, 0L, SEEK_END);
	start  = lseek(fd, 0L, SEEK_SET);
//LOGI("%s: %d fd=%d, start=%d, length=%d", __func__, __LINE__, fd, start, length);

    // configure audio source
    SLDataLocator_AndroidFD loc_fd = {SL_DATALOCATOR_ANDROIDFD, (SLint32)fd, start, length};
    SLDataFormat_MIME format_mime = {SL_DATAFORMAT_MIME, NULL, SL_CONTAINERTYPE_UNSPECIFIED};
    SLDataSource audioSrc = {&loc_fd, &format_mime};

    // configure audio sink
    SLDataLocator_OutputMix loc_outmix = {SL_DATALOCATOR_OUTPUTMIX, outputMixObject};
    SLDataSink audioSnk = {&loc_outmix, NULL};

    // create audio player
    const SLInterfaceID ids[3] = {SL_IID_SEEK, SL_IID_MUTESOLO, SL_IID_VOLUME};
    const SLboolean req[3] = {SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE};
    result = (*engineEngine)->CreateAudioPlayer(engineEngine, &fdPlayerObject, &audioSrc, &audioSnk,
            3, ids, req);
    assert(SL_RESULT_SUCCESS == result);
    (void)result;

    // realize the player
    result = (*fdPlayerObject)->Realize(fdPlayerObject, SL_BOOLEAN_FALSE);
    assert(SL_RESULT_SUCCESS == result);
    (void)result;

    // get the play interface
    result = (*fdPlayerObject)->GetInterface(fdPlayerObject, SL_IID_PLAY, &fdPlayerPlay);
    assert(SL_RESULT_SUCCESS == result);
    (void)result;

    // get the seek interface
    result = (*fdPlayerObject)->GetInterface(fdPlayerObject, SL_IID_SEEK, &fdPlayerSeek);
    assert(SL_RESULT_SUCCESS == result);
    (void)result;

    // get the mute/solo interface
    result = (*fdPlayerObject)->GetInterface(fdPlayerObject, SL_IID_MUTESOLO, &fdPlayerMuteSolo);
    assert(SL_RESULT_SUCCESS == result);
    (void)result;

    // get the volume interface
    result = (*fdPlayerObject)->GetInterface(fdPlayerObject, SL_IID_VOLUME, &fdPlayerVolume);
    assert(SL_RESULT_SUCCESS == result);
    (void)result;

    // enable whole file looping
    result = (*fdPlayerSeek)->SetLoop(fdPlayerSeek, SL_BOOLEAN_TRUE, 0, SL_TIME_UNKNOWN);
    assert(SL_RESULT_SUCCESS == result);
    (void)result;

    return TRUE;
}


// set the playing state for the asset audio player
//void Java_com_example_nativeaudio_NativeAudio_setPlayingAssetAudioPlayer(JNIEnv* env,
//        jclass clazz, jboolean isPlaying)
void NativeAudio_setPlayingFileAudioPlayer(bool isPlaying)
{
    SLresult result;

    // make sure the asset audio player was created
    if (NULL != fdPlayerPlay) {

        // set the player's state
        result = (*fdPlayerPlay)->SetPlayState(fdPlayerPlay, isPlaying ?
            SL_PLAYSTATE_PLAYING : SL_PLAYSTATE_PAUSED);
        assert(SL_RESULT_SUCCESS == result);
        (void)result;
    }
}


void NativeAudio_setLoopingFileAudioPlayer(bool isLooping)
{
    SLresult result;

    // make sure the URI audio player was created
    if (NULL != fdPlayerSeek) {

        // set the looping state
        result = (*fdPlayerSeek)->SetLoop(fdPlayerSeek, (SLboolean) isLooping, 0,
                SL_TIME_UNKNOWN);
        assert(SL_RESULT_SUCCESS == result);
        (void)result;
    }
}


// create audio recorder: recorder is not in fast path
//    like to avoid excessive re-sampling while playing back from Hello & Android clip
//jboolean Java_com_example_nativeaudio_NativeAudio_createAudioRecorder(JNIEnv* env, jclass clazz)
bool NativeAudio_createAudioRecorder()
{
    SLresult result;

	is_rec = FALSE;

    // configure audio source
    SLDataLocator_IODevice loc_dev = {SL_DATALOCATOR_IODEVICE, SL_IODEVICE_AUDIOINPUT,
            SL_DEFAULTDEVICEID_AUDIOINPUT, NULL};
    SLDataSource audioSrc = {&loc_dev, NULL};

    // configure audio sink
    SLDataLocator_AndroidSimpleBufferQueue loc_bq = {SL_DATALOCATOR_ANDROIDSIMPLEBUFFERQUEUE, 2};
    SLDataFormat_PCM format_pcm = {
		SL_DATAFORMAT_PCM, 
		1, 
//		SL_SAMPLINGRATE_8, //16,
		SL_SAMPLINGRATE_44_1,
		SL_PCMSAMPLEFORMAT_FIXED_16, 
        SL_PCMSAMPLEFORMAT_FIXED_16,
        SL_SPEAKER_FRONT_CENTER, 
        SL_BYTEORDER_LITTLEENDIAN
        };
    SLDataSink audioSnk = {&loc_bq, &format_pcm};

    // create audio recorder
    // (requires the RECORD_AUDIO permission)
    const SLInterfaceID id[1] = {SL_IID_ANDROIDSIMPLEBUFFERQUEUE};
    const SLboolean req[1] = {SL_BOOLEAN_TRUE};
    result = (*engineEngine)->CreateAudioRecorder(engineEngine, &recorderObject, &audioSrc,
            &audioSnk, 1, id, req);
    if (SL_RESULT_SUCCESS != result) {
        return FALSE;
    }

    // realize the audio recorder
    result = (*recorderObject)->Realize(recorderObject, SL_BOOLEAN_FALSE);
    if (SL_RESULT_SUCCESS != result) {
        return FALSE;
    }

    // get the record interface
    result = (*recorderObject)->GetInterface(recorderObject, SL_IID_RECORD, &recorderRecord);
    assert(SL_RESULT_SUCCESS == result);
    (void)result;

    // get the buffer queue interface
    result = (*recorderObject)->GetInterface(recorderObject, SL_IID_ANDROIDSIMPLEBUFFERQUEUE,
            &recorderBufferQueue);
    assert(SL_RESULT_SUCCESS == result);
    (void)result;

    // register callback on the buffer queue
    result = (*recorderBufferQueue)->RegisterCallback(recorderBufferQueue, bqRecorderCallback,
            NULL);
    assert(SL_RESULT_SUCCESS == result);
    (void)result;

    return TRUE;
}


// set the recording state for the audio recorder
//void Java_com_example_nativeaudio_NativeAudio_startRecording(JNIEnv* env, jclass clazz)
bool NativeAudio_startRecording(int *nRecBuf)
{
    SLresult result;

//    if (pthread_mutex_trylock(&audioEngineLock)) {
//        return FALSE;
//    }
    // in case already recording, stop recording and clear buffer queue
    result = (*recorderRecord)->SetRecordState(recorderRecord, SL_RECORDSTATE_STOPPED);
    assert(SL_RESULT_SUCCESS == result);
    (void)result;
    result = (*recorderBufferQueue)->Clear(recorderBufferQueue);
    assert(SL_RESULT_SUCCESS == result);
    (void)result;

    // the buffer is not valid for playback yet
    recorderSize = 0;

	curRecBuf = 0;

    // enqueue an empty buffer to be filled by the recorder
    // (for streaming recording, we would enqueue at least 2 empty buffers to start things off)
    result = (*recorderBufferQueue)->Enqueue(recorderBufferQueue, recorderBuffers[curRecBuf],
            RECORDER_FRAMES * sizeof(short));
    // the most likely other result is SL_RESULT_BUFFER_INSUFFICIENT,
    // which for this code example would indicate a programming error
    assert(SL_RESULT_SUCCESS == result);
    (void)result;

    // start recording
    result = (*recorderRecord)->SetRecordState(recorderRecord, SL_RECORDSTATE_RECORDING);
    assert(SL_RESULT_SUCCESS == result);
    (void)result;
	
//    pthread_mutex_unlock(&audioEngineLock);

	is_rec = TRUE;
	*nRecBuf = curRecBuf;

	return TRUE;
}


int NativeAudio_getRecordingResult(int *nbuf, char **pbuf)
{
	
	int curRecBuf_ = curRecBuf ^ 1;
//    if (pthread_mutex_trylock(&audioEngineLock)) {
	if (*nbuf == curRecBuf_){
//LOGI("%s: %d 1 *nbuf=%d, curRecBuf=%d", __func__, __LINE__, *nbuf, curRecBuf);
        return 0;
    }
//LOGI("%s: %d 2 *nbuf=%d, curRecBuf=%d", __func__, __LINE__, *nbuf, curRecBuf);

	*pbuf = (char*)recorderBuffers[curRecBuf_];

//    pthread_mutex_unlock(&audioEngineLock);

	*nbuf = curRecBuf_;
	return recorderSize;
}


// shut down the native audio system
//void Java_com_example_nativeaudio_NativeAudio_shutdown(JNIEnv* env, jclass clazz)
void NativeAudio_shutdown()
{

    // destroy buffer queue audio player object, and invalidate all associated interfaces
    if (bqPlayerObject != NULL) {
        (*bqPlayerObject)->Destroy(bqPlayerObject);
        bqPlayerObject = NULL;
        bqPlayerPlay = NULL;
        bqPlayerBufferQueue = NULL;
        bqPlayerEffectSend = NULL;
        bqPlayerMuteSolo = NULL;
        bqPlayerVolume = NULL;
    }

    // destroy file descriptor audio player object, and invalidate all associated interfaces
    if (fdPlayerObject != NULL) {
        (*fdPlayerObject)->Destroy(fdPlayerObject);
        fdPlayerObject = NULL;
        fdPlayerPlay = NULL;
        fdPlayerSeek = NULL;
        fdPlayerMuteSolo = NULL;
        fdPlayerVolume = NULL;
    }

    // destroy URI audio player object, and invalidate all associated interfaces
    if (uriPlayerObject != NULL) {
        (*uriPlayerObject)->Destroy(uriPlayerObject);
        uriPlayerObject = NULL;
        uriPlayerPlay = NULL;
        uriPlayerSeek = NULL;
        uriPlayerMuteSolo = NULL;
        uriPlayerVolume = NULL;
    }

    // destroy audio recorder object, and invalidate all associated interfaces
    if (recorderObject != NULL) {
        (*recorderObject)->Destroy(recorderObject);
        recorderObject = NULL;
        recorderRecord = NULL;
        recorderBufferQueue = NULL;
    }

    // destroy output mix object, and invalidate all associated interfaces
    if (outputMixObject != NULL) {
        (*outputMixObject)->Destroy(outputMixObject);
        outputMixObject = NULL;
        outputMixEnvironmentalReverb = NULL;
    }

    // destroy engine object, and invalidate all associated interfaces
    if (engineObject != NULL) {
        (*engineObject)->Destroy(engineObject);
        engineObject = NULL;
        engineEngine = NULL;
    }

    pthread_mutex_destroy(&audioEngineLock);
}


void NativeAudio_shutdownFile()
{

    // destroy file descriptor audio player object, and invalidate all associated interfaces
    if (fdPlayerObject != NULL) {
        (*fdPlayerObject)->Destroy(fdPlayerObject);
        fdPlayerObject = NULL;
        fdPlayerPlay = NULL;
        fdPlayerSeek = NULL;
        fdPlayerMuteSolo = NULL;
        fdPlayerVolume = NULL;
    }

	if(glob_fd != -1)
		close(glob_fd);
	glob_fd = -1;
}


void NativeAudio_shutdownUri()
{
    // destroy URI audio player object, and invalidate all associated interfaces
    if (uriPlayerObject != NULL) {
        (*uriPlayerObject)->Destroy(uriPlayerObject);
        uriPlayerObject = NULL;
        uriPlayerPlay = NULL;
        uriPlayerSeek = NULL;
        uriPlayerMuteSolo = NULL;
        uriPlayerVolume = NULL;
    }
}


void NativeAudio_shutdownAudioRecorder()
{
    // destroy audio recorder object, and invalidate all associated interfaces
    if (recorderObject != NULL) {
        (*recorderObject)->Destroy(recorderObject);
        recorderObject = NULL;
        recorderRecord = NULL;
        recorderBufferQueue = NULL;
    }

	is_rec = FALSE;
}


void NativeAudio_shutdownBufferQueueAudioPlayer()
{
    // destroy buffer queue audio player object, and invalidate all associated interfaces
    if (bqPlayerObject != NULL) {
        (*bqPlayerObject)->Destroy(bqPlayerObject);
        bqPlayerObject = NULL;
        bqPlayerPlay = NULL;
        bqPlayerBufferQueue = NULL;
        bqPlayerEffectSend = NULL;
        bqPlayerMuteSolo = NULL;
        bqPlayerVolume = NULL;
    }

	if(nextBuffers[curBuf])
		free(nextBuffers[curBuf]);
	nextBuffers[curBuf] = NULL;
	
	nextSizes[curBuf] = 0;
	
	curBuf ^= 1;
	
	if(nextBuffers[curBuf])
		free(nextBuffers[curBuf]);
	nextBuffers[curBuf] = NULL;
	
	nextSizes[curBuf] = 0;
	
	is_play = FALSE;

}




