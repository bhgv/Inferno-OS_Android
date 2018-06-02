#include	"dat.h"
#include	"fns.h"
#include	"error.h"
#include	"audio.h"

//#include "../port/audio-tbls.c"


#include <stdbool.h>
#define TRUE true
#define FALSE false

//#include <SLES/OpenSLES.h> 
//#include <SLES/OpenSLES_Android.h> 


#include <android/log.h>
	
#define  LOG_TAG    "Inferno DAU"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGW(...)  __android_log_print(ANDROID_LOG_WARN,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)



Dirtab audiotab[] =
{
	".",		{Qdir, 0, QTDIR},	0,	0555,
	"audio",	{Qaudio},	0,	0666,
	"audioctl",	{Qaudioctl},	0,	0666,
};



extern void NativeAudio_createEngine();
extern void NativeAudio_shutdown();


extern bool NativeAudio_createUriAudioPlayer(char *uri);
extern void NativeAudio_shutdownUri();

extern void NativeAudio_setPlayingUriAudioPlayer(bool isPlaying);
extern void NativeAudio_setLoopingUriAudioPlayer(bool isLooping);

extern void NativeAudio_setChannelMuteUriAudioPlayer(int chan, bool mute);
extern void NativeAudio_setChannelSoloUriAudioPlayer(int chan, bool solo);
extern int NativeAudio_getNumChannelsUriAudioPlayer();

extern void NativeAudio_setVolumeUriAudioPlayer(int millibel);
extern void NativeAudio_setMuteUriAudioPlayer(bool mute);

extern void NativeAudio_enableStereoPositionUriAudioPlayer(bool enable);
extern void NativeAudio_setStereoPositionUriAudioPlayer(int permille);
extern bool NativeAudio_enableReverb(bool enabled);


extern void NativeAudio_createBufferQueueAudioPlayer(int sampleRate, int bufSize);
extern void NativeAudio_shutdownBufferQueueAudioPlayer();

extern bool NativeAudio_setBufClip(int count, char* buf, int buf_size);


extern bool NativeAudio_createFileAudioPlayer(char *filename);
extern void NativeAudio_shutdownFile();

extern void NativeAudio_setPlayingFileAudioPlayer(bool isPlaying);
extern void NativeAudio_setLoopingFileAudioPlayer(bool isLooping);


extern bool NativeAudio_createAudioRecorder();
extern void NativeAudio_shutdownAudioRecorder();

extern bool NativeAudio_startRecording(int *nRecBuf);
extern int NativeAudio_getRecordingResult(int *nbuf, char **pbuf);

int sampleRate = 44100; //8000; //
int bufSize = 512; //8 * 1024;


static char 
	*buf_read=nil, 
	*buf_write=nil;

static int 
	rd_total=0, 
	rd_pos=0, 
	
	wr_total=0, 
	wr_pos=0;

static bool
	is_rec=0,
	is_buf=0,
	is_play=0;

static int nRecBuf;
static int nBuf;


extern char rootdir[];





void audioctl_wr_pars(char* in, int count);


static void
audioinit(void)
{
	//audio_file_init();
	NativeAudio_createEngine();
	
	buf_read = nil;
	buf_write = nil;
	
	rd_total = 0;
	rd_pos = 0;
	
	wr_total = 0;
	wr_pos = 0;

	is_rec = FALSE;
	is_buf = FALSE;

	nRecBuf = 0;
	nBuf = 0;
}


static void
audioshutdown(void)
{
	NativeAudio_shutdown();
}


static Chan*
audioattach(char *spec)
{
	return devattach('A', spec);
}


static Walkqid*
audiowalk(Chan *c, Chan *nc, char **name, int nname)
{
	return devwalk(c, nc, name, nname, audiotab, nelem(audiotab), devgen);
}


static int
audiostat(Chan *c, uchar *db, int n)
{
	return devstat(c, db, n, audiotab, nelem(audiotab), devgen);
}


static Chan*
audioopen(Chan *c, int omode)
{
	c = devopen(c, omode, audiotab, nelem(audiotab), devgen);
	if(waserror()){
		c->flag &= ~COPEN;
		nexterror();
	}
	switch(c->qid.path) {
	case Qdir:
	case Qaudioctl:
		break;
	case Qaudio:
LOGI("%s: %d omode=%d", __func__, __LINE__, omode);
		switch(omode & 3){
			case OREAD:
				if(buf_read) 
					free(buf_read);
				buf_read = nil;
				
				rd_total = 0;
				rd_pos = 0;

				nRecBuf = 0;
				
LOGI("%s: %d OREAD", __func__, __LINE__);
				NativeAudio_createAudioRecorder();
//LOGI("%s: %d", __func__, __LINE__);
//				while( !
				NativeAudio_startRecording(&nRecBuf);
//					);
				is_rec = TRUE;
				break;
			
			case OWRITE:
				if(buf_write) 
					free(buf_write);
				buf_write = nil;
				
				wr_total = 0;
				wr_pos = 0;

				nBuf = 0;
				
LOGI("%s: %d OWRITE", __func__, __LINE__);
				NativeAudio_createBufferQueueAudioPlayer(sampleRate, bufSize);
				is_buf = TRUE;
				is_play = TRUE;
				break;
		}
		
		//audio_file_open(c, c->mode);
		break;
	default:
		error(Egreg);
	}
	poperror();
	return c;
}


static void
audioclose(Chan *c)
{
	if((c->flag & COPEN) == 0)
		return;

	switch(c->qid.path) {
	case Qdir:
	case Qaudioctl:
		break;
	case Qaudio:
		if(is_rec){
			NativeAudio_shutdownAudioRecorder();
			
			if(buf_read) 
				free(buf_read);
			buf_read = nil;
			
			rd_total = 0;
			rd_pos = 0;
			
			is_rec = FALSE;
		}
		
		if(is_buf){
			NativeAudio_shutdownBufferQueueAudioPlayer();
			
			if(buf_write) 
				free(buf_write);
			buf_write = nil;

			wr_total = 0;
			wr_pos = 0;
			
			is_buf = FALSE;
			is_play = FALSE;
		}

		//audio_file_close(c);
		break;
	default:
		error(Egreg);
	}
}


//static int ctlsummary(char*, int, Audio_t*);

static long
audioread(Chan *c, void *va, long count, vlong offset)
{
	char *buf;
	int n;

	if(c->qid.type & QTDIR)
		return devdirread(c, va, count, audiotab, nelem(audiotab), devgen);
	
	switch(c->qid.path) {
	case Qaudio:
	{
		int sz;
		int chunk;
		char *buf;
		int i;

		if(count == 0)
			return 0;
		
		sz = 0;
		chunk = 0;
		
		while(chunk < count){
			if(rd_pos >= rd_total){
//LOGI("%s: %d", __func__, __LINE__);
				while( (sz = NativeAudio_getRecordingResult(&nRecBuf, &buf) ) == 0 )
					limbosleep(5);
//LOGI("%s: %d", __func__, __LINE__);
				if(buf_read) 
					free(buf_read);
				buf_read = malloc(2*sz + 4);
				for(i=0; i < sz/sizeof(short); i++){
					((short*)buf_read)[2*i + 0] = ((short*)buf)[i];
					((short*)buf_read)[2*i + 1] = ((short*)buf)[i];
				}
				//memmove(buf_read, buf, sz);
				rd_pos = 0;
				rd_total = 2*sz;
			}
			
			sz = rd_total - rd_pos;
			if(sz > count - chunk) 
				sz = count - chunk;

			memmove(((char*)va) + chunk, buf_read + rd_pos, sz);

			chunk += sz;
			rd_pos += sz;
		}
		return chunk; //audio_file_read(c, va, count, offset);
	}
	
	case Qaudioctl:
		buf = smalloc(READSTR);
		if(waserror()){
			free(buf);
			nexterror();
		}
		n = 0; //ctlsummary(buf, READSTR, getaudiodev());
		count = readstr(offset, va, n, buf);
		poperror();
		free(buf);
		return count;
	}
	return 0;
}


static long
audiowrite(Chan *c, void *va, long count, vlong offset)
{
	switch(c->qid.path) {
	case Qaudio:
//LOGI("%s: %d", __func__, __LINE__);
		if(is_play)
		while( !NativeAudio_setBufClip(&nBuf, ((char*)va) /*+ offset*/, count) )
			limbosleep(5);
//LOGI("%s: %d", __func__, __LINE__);
	
		return count; //audio_file_write(c, va, count, offset);

	case Qaudioctl:
		audioctl_wr_pars(va, count);
		
		return count;
		//return audio_ctl_write(c, va, count, offset);
	}
	return 0;
}


void audioctl_load_pars(char **pars, int npars){
	if( npars > 1 && !strcmp(pars[0], "file") ){
		char *path;
		int res;
		int l = strlen(pars[1]) + strlen(rootdir) + 1 + 1;
		
		path = malloc(l + 4);
		
		snprint(path, l+1, "%s/%s", rootdir, pars[1]);
		res = NativeAudio_createFileAudioPlayer(path);
		
		free(path);
	}else if( npars > 1 && !strcmp(pars[0], "uri") ){
		int res = NativeAudio_createUriAudioPlayer(pars[1]);
//LOGI("%s: %d res=%d", __func__, __LINE__, res);
	}
}


void audioctl_unload_pars(char **pars, int npars){
	if( npars > 0 && !strcmp(pars[0], "file") ){
		
		NativeAudio_shutdownFile();
	}else if( npars > 0 && !strcmp(pars[0], "uri") ){
	
		NativeAudio_shutdownUri();
	}else if( npars > 0 && !strcmp(pars[0], "buf") ){
		is_play = FALSE;
		NativeAudio_shutdownBufferQueueAudioPlayer();
	}
}


void audioctl_play_pars(char **pars, int npars, bool is_play){
	if( npars > 0 && !strcmp(pars[0], "file") ){
		
		NativeAudio_setPlayingFileAudioPlayer(is_play);
	}else if( npars > 0 && !strcmp(pars[0], "uri") ){
	
		NativeAudio_setPlayingUriAudioPlayer(is_play);
	}
}


void audioctl_loop_pars(char **pars, int npars, bool is_loop){
	if( npars > 0 && !strcmp(pars[0], "file") ){
		
		NativeAudio_setLoopingUriAudioPlayer(is_loop);
	}else if( npars > 0 && !strcmp(pars[0], "uri") ){
	
		NativeAudio_setLoopingFileAudioPlayer(is_loop);
	}
}


void audioctl_wr_pars(char* in, int count)
{
	int i;
	char *pars[100];
	int npars = 0;
	int maxpars = sizeof(pars)/sizeof(char*);
	
	int first_char = 1;

	memset(pars, 0, sizeof(pars));
	
	for(i = 0; i < count && npars < maxpars; i++){
		char c = in[i];
		if(
			c == ' '  ||
			c == '\t' ||
			c == '\n' ||
			c == '\r' 
		){
			in[i] = '\0';
			first_char = 1;
		}else{
			if(first_char){
				pars[npars] = &in[i];
				npars++;
				first_char = 0;
			}
		}
	}
	if(npars > 0){
		if( npars > 2 && !strcmp(pars[0], "load") ){
			
			audioctl_load_pars(&pars[1], npars-1);
			return;
		}else if( npars > 1 && !strcmp(pars[0], "unload") ){
			audioctl_unload_pars(&pars[1], npars-1);
			return;
		}else if( npars > 1 && !strcmp(pars[0], "play") ){
			audioctl_play_pars(&pars[1], npars-1, TRUE);
			return;
		}else if( npars > 1 && !strcmp(pars[0], "stop") ){
			audioctl_play_pars(&pars[1], npars-1, FALSE);
			return;
		}else if( npars > 2 && !strcmp(pars[0], "loop") ){
			int is_loop;
			if( !strcmp(pars[1], "off") )
				is_loop = 0;
			else if( !strcmp(pars[1], "on") )
				is_loop = 1;
			else
				return;
			
			audioctl_loop_pars(&pars[2], npars-2, is_loop);
			return;
		}
	}
}


#if 0
static int sval(char*, unsigned long*, ulong, ulong);
static int str2val(svp_t*, char*, ulong*);
static char* val2str(svp_t*, ulong);

int
audioparse(char* args, int len, Audio_t *t)
{
	int i, n;
	ulong v;
	Cmdbuf *cb;
	ulong tf;
	Audio_t info = *t;

	cb = parsecmd(args, len);
	if(waserror()){
		free(cb);
		return 0;
	}

	tf = 0;
	n = cb->nf;
	for(i = 0; i < cb->nf-1; i++) {
		if(strcmp(cb->f[i], "in") == 0){
			tf |= AUDIO_IN_FLAG;
			continue;
		}
		if(strcmp(cb->f[i], "out") == 0) {
			tf |= AUDIO_OUT_FLAG;
			continue;
		}
		if(tf == 0)
			tf = AUDIO_IN_FLAG | AUDIO_OUT_FLAG;
		if(strcmp(cb->f[i], "bits") == 0) {
			if(!str2val(audio_bits_tbl, cb->f[i+1], &v))
				break;
			i++;
			if(tf & AUDIO_IN_FLAG) {
				info.in.flags |= AUDIO_BITS_FLAG | AUDIO_MOD_FLAG;
				info.in.bits = v;
			}
			if(tf & AUDIO_OUT_FLAG) {
				info.out.flags |= AUDIO_BITS_FLAG | AUDIO_MOD_FLAG;
				info.out.bits = v;
			}
		} else if(strcmp(cb->f[i], "buf") == 0) {
			if(!sval(cb->f[i+1], &v, Audio_Max_Val, Audio_Min_Val))
				break;
			i++;
			if(tf & AUDIO_IN_FLAG) {
				info.in.flags |= AUDIO_BUF_FLAG | AUDIO_MOD_FLAG;
				info.in.buf = v;
			}
			if(tf & AUDIO_OUT_FLAG) {
				info.out.flags |= AUDIO_BUF_FLAG | AUDIO_MOD_FLAG;
				info.out.buf = v;
			}
		} else if(strcmp(cb->f[i], "chans") == 0) {
			if(!str2val(audio_chan_tbl, cb->f[i+1], &v))
				break;
			i++;
			if(tf & AUDIO_IN_FLAG) {
				info.in.flags |= AUDIO_CHAN_FLAG | AUDIO_MOD_FLAG;
				info.in.chan = v;
			}
			if(tf & AUDIO_OUT_FLAG) {
				info.out.flags |= AUDIO_CHAN_FLAG | AUDIO_MOD_FLAG;
				info.out.chan = v;
			}
		} else if(strcmp(cb->f[i], "indev") == 0) {
			if(!str2val(audio_indev_tbl, cb->f[i+1], &v))
				break;
			i++;
			info.in.flags |= AUDIO_DEV_FLAG | AUDIO_MOD_FLAG;
			info.in.dev = v;
		} else if(strcmp(cb->f[i], "outdev") == 0) {
			if(!str2val(audio_outdev_tbl, cb->f[i+1], &v))
				break;
			i++;
			info.out.flags |= AUDIO_DEV_FLAG | AUDIO_MOD_FLAG;
			info.out.dev = v;
		} else if(strcmp(cb->f[i], "enc") == 0) {
			if(!str2val(audio_enc_tbl, cb->f[i+1], &v))
				break;
			i++;
			if(tf & AUDIO_IN_FLAG) {
				info.in.flags |= AUDIO_ENC_FLAG | AUDIO_MOD_FLAG;
				info.in.enc = v;
			}
			if(tf & AUDIO_OUT_FLAG) {
				info.out.flags |= AUDIO_ENC_FLAG | AUDIO_MOD_FLAG;
				info.out.enc = v;
			}
		} else if(strcmp(cb->f[i], "rate") == 0) {
			if(!str2val(audio_rate_tbl, cb->f[i+1], &v))
				break;
			i++;
			if(tf & AUDIO_IN_FLAG) {
				info.in.flags |= AUDIO_RATE_FLAG | AUDIO_MOD_FLAG;
				info.in.rate = v;
			}
			if(tf & AUDIO_OUT_FLAG) {
				info.out.flags |= AUDIO_RATE_FLAG | AUDIO_MOD_FLAG;
				info.out.rate = v;
			}
		} else if(strcmp(cb->f[i], "vol") == 0) {
			if(!sval(cb->f[i+1], &v, Audio_Max_Val, Audio_Min_Val))
				break;
			i++;
			if(tf & AUDIO_IN_FLAG) {
				info.in.flags |= AUDIO_VOL_FLAG | AUDIO_MOD_FLAG;
				info.in.left = v;
				info.in.right = v;
			}
			if(tf & AUDIO_OUT_FLAG) {
				info.out.flags |= AUDIO_VOL_FLAG | AUDIO_MOD_FLAG;
				info.out.left = v;
				info.out.right = v;
			}
		} else if(strcmp(cb->f[i], "left") == 0) {
			if(!sval(cb->f[i+1], &v, Audio_Max_Val, Audio_Min_Val))
				break;
			i++;
			if(tf & AUDIO_IN_FLAG) {
				info.in.flags |= AUDIO_LEFT_FLAG | AUDIO_MOD_FLAG;
				info.in.left = v;
			}
			if(tf & AUDIO_OUT_FLAG) {
				info.out.flags |= AUDIO_LEFT_FLAG | AUDIO_MOD_FLAG;
				info.out.left = v;
			}
		} else if(strcmp(cb->f[i], "right") == 0) {
			if(!sval(cb->f[i+1], &v, Audio_Max_Val, Audio_Min_Val))
				break;
			i++;
			if(tf & AUDIO_IN_FLAG) {
				info.in.flags |= AUDIO_RIGHT_FLAG | AUDIO_MOD_FLAG;
				info.in.right = v;
			}
			if(tf & AUDIO_OUT_FLAG) {
				info.out.flags |= AUDIO_RIGHT_FLAG | AUDIO_MOD_FLAG;
				info.out.right = v;
			}
		}else
			break;
	}
	poperror();
	free(cb);

	if(i < n)
		return 0;

	*t = info;	/* set information back */
	return 1;
}

static char*
audioparam(char* p, char* e, char* name, int val, svp_t* tbl)
{
	char *s;
	svp_t *sv;

	if((s = val2str(tbl, val)) != nil){
		p = seprint(p, e, "%s %s", name, s);	/* current setting */
		for(sv = tbl; sv->s != nil; sv++)
			if(sv->v != val)
				p = seprint(p, e, " %s", sv->s);	/* other possible values */
		p = seprint(p, e, "\n");
	}else
		p = seprint(p, e, "%s unknown\n", name);
	return p;
}

static char*
audioioparam(char* p, char* e, char* name, int ival, int oval, svp_t* tbl)
{
	if(ival == oval)
		return audioparam(p, e, name, ival, tbl);
	p = audioparam(seprint(p, e, "in "), e, name, ival, tbl);
	p = audioparam(seprint(p, e, "out "), e, name, oval, tbl);
	return p;
}

static int
ctlsummary(char *buf, int bsize, Audio_t *adev)
{
	Audio_d *in, *out;
	char	*p, *e;

	in = &adev->in;
	out = &adev->out;

	p = buf;
	e = p + bsize;

	p = audioparam(p, e, "indev", in->dev, audio_indev_tbl);
	p = audioparam(p, e, "outdev", out->dev, audio_outdev_tbl);
	p = audioioparam(p, e, "enc", in->enc, out->enc, audio_enc_tbl);
	p = audioioparam(p, e, "rate", in->rate, out->rate, audio_rate_tbl);
	p = audioioparam(p, e, "bits", in->bits, out->bits, audio_bits_tbl);	/* this one is silly */
	p = audioioparam(p, e, "chans", in->chan, out->chan, audio_chan_tbl);
	/* TO DO: minimise in/out left/right where possible */
	if(in->left != in->right){
		p = seprint(p, e, "in left %d 0 100\n", in->left);
		p = seprint(p, e, "in right %d 0 100\n", in->right);
	}else
		p = seprint(p, e, "in %d 0 100\n", in->right);
	if(out->left != out->right){
		p = seprint(p, e, "out left %d 0 100\n", out->left);
		p = seprint(p, e, "out right %d 0 100\n", out->right);
	}else
		p = seprint(p, e, "out %d 0 100\n", out->right);
	p = seprint(p, e, "in buf %d %d %d\n", in->buf, Audio_Min_Val, Audio_Max_Val);
	p = seprint(p, e, "out buf %d %d %d\n", out->buf, Audio_Min_Val, Audio_Max_Val);

	return p-buf;
}

void
audio_info_init(Audio_t *t)
{
	t->in = Default_Audio_Format;
	t->in.dev = Default_Audio_Input;
	t->out = Default_Audio_Format;
	t->out.dev = Default_Audio_Output;
}
#endif

static int
str2val(svp_t* t, char* s, ulong *v)
{
	if(t == nil || s == nil)
		return 0;
	for(; t->s != nil; t++) {
		if(strncmp(t->s, s, strlen(t->s)) == 0) {
			*v = t->v;
			return 1;
		}
	}
	return 0;
}

static char*
val2str(svp_t* t, ulong v)
{
	if(t == nil)
		return nil;
	for(; t->s != nil; t++)
		if(t->v == v)
			return t->s;
	return nil;
}

static int 
sval(char* buf, ulong* v, ulong max, ulong min)
{
	unsigned long val = strtoul(buf, 0, 10);

	if(val > max || val < min)
		return 0;
	*v = val;
	return 1;
}

Dev audio_andrdevtab = {
        'A',
        "audio",

        audioinit,
        audioattach,
        audiowalk,
        audiostat,
        audioopen,
        devcreate,
        audioclose,
        audioread,
        devbread,
        audiowrite,
        devbwrite,
        devremove,
        devwstat
};

