# Inferno-OS_Android

![Screenshot](doku/screenshot.jpg)

for Android > v4.0 (api 14)

it is based on the last [official sources from Vitanuova](https://bitbucket.org/inferno-os/inferno-os/).

## What is working now
* Gui. for compatibility main gui app is `wm/awm` (it loads wm/awm after start). sources are in the `/appl/awm` and `/appl/alib`,
* Touch screen. Only single touches. Don't know where to use multitouches in the Inferno,
* Files. File-tree are stored in the `/sdcard/Inferno` folder (permission), 
* Network. Both styx and the regular tcp connections (permission),

## What was changed
* Gui. Bigger icons, bigger keys on the keyboard, bigger captions on windows, some icons were changed (because of sizes),
* Display output. Because of Android. This way is a little experimental still and may be changed in the future.

## What was added
* Was added support of `.PNG` and `.SVG` images. They may used now in the places where may be used .BIT images. For example as a parameter `-bitmap` of Tk controls calls.

* A possibility to resize `.SVG` or `.PNG` images in time of loading them by Tk. (`bitmap :<new size>:<image-path>.svg-or-png`)

* `.TTF` fonts (and maybe `.T1` and other) is supported internally using embedded libfreetype. to use, specify them as subfonts in the font files,

* command line (in the format of the regular emu commang line). has restrictions (mostly in the graphic parameters and the jit). because of restrictions of the hardware. [JIT compiler was buit for other kind of FPU](https://bitbucket.org/inferno-os/inferno-os/issues/344/charon-doesnt-start-on-the-open-pandora#comment-31995777)

* `/dev/audio` and `/dev/audioctl` devices

first it should be mapped to `/dev` fs:
```
bind -b '#A' /dev
```
### possibilities:

* * reading of `/dev/audio` will reads the phone's mic (44.1kHz, 16bit, stereo, raw wave without headers and compression). ex:
```
cat /dev/audio > snd.raw
```
* * writing to `/dev/audio` will outputs the data was written to phones speaker (44.1kHz, 16bit, stereo, raw wave without headers and compression). ex:
```
cat snd.raw > /dev/audio
```
* * `/dev/audioctl` supports now next commands (only writing to):
* * * `load file <file path in the inferno's fs>` - loads the specified file, but don't start to play,
* * * `load uri <uri address of a stream to play>` - loads the specified network stream, but don't start to play,
* * * `unload file` - unloads last loaded file and free used resources,
* * * `unload uri` - unloads last loaded network stream and free used resources,
* * * `play file` - play the loaded file,
* * * `play uri` - play the loaded uri,
* * * `stop file` - stop playing of the file,
* * * `stop uri` - stop playing of the network's stream,
* * * `loop file` or `loop uri` - loops playing of the file or the stream.

all sound streams: record, output of raw wave (`/dev/audio`), playing of a file and network stream use separate buffers and may work simultaneously.

ex:
```
echo load file /mp3/a_music.mp3 > /dev/audioctl
echo play file > /dev/audioctl
```
or
```
echo load uri http://ice1.somafm.com/dubstep-128-mp3 > /dev/audioctl
echo play uri > /dev/audioctl
```
(thanks to somafm.com network radio for provided demo net stream)

* 2nd and 3rd mouse buttons. they are emulated using multitouch possibilities.

### how to use
point or select what you need with 1 finger, after tap somewhere with 1 or 2 more fingers. this will couse a click of 2nd or 3rd mouse button. 

coordinates of the click is the coordinates of the first finger.

* copy/snarf - paste

copy-paste functionality is working now. but only with texts yet.

Inferno's copy paste buffer is separated from the Android copy-paste buffer. actually no way to copy-paste between Inferno and Android.


## Build media note
It is built under Windows. But if you are using Linux it is easy to build it under Linux. only a pair of changes. go to the "inferno-os" folder and rewrite "bld.bat" script to Linux style. also do not forget to configure to Linux tools by modifying "makeconfig" script and so on.

## Dependencies
* Android Studio > v3.0
* Cmake plugin for Android Studio
* NDK 

# how to build

## Windows host
```
cd inferno-os
bld.bat
```
after the successful building of the inferno libs (`./inferno-os/Android/arm/lib`)
open this project in the Android Studio and build apk.

# how to run
install this apk on the android
copy this inferno tree (`./inferno-os`) to android by the path `/sdcard/Inferno`.

run it

![Acme & Charon](doku/acme_charon.jpg)
