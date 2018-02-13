#include "lib9.h"
#include "kernel.h"
#include "draw.h"



#ifdef ANDROID
#include <android/log.h>

#define  LOG_TAG    "inferno RSF_FT"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGW(...)  __android_log_print(ANDROID_LOG_WARN,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
#else
#define  LOGI(...)  printf(__VA_ARGS__)
#define  LOGW(...)  
#define  LOGE(...)  
#endif


#include "freetype/freetype.h"
#include "freetype.h"


int
is_subfont_ft(char *name){
	char c1, c2, c3, c4;
	int r;
	int i = strlen(name) - 1;
	
	if(i >= 0){
		c1 = name[i-3];
		c2 = name[i-2];
		c3 = name[i-1];
		c4 = name[i-0];
	}else
		return 0;

	r = (
		c1 == '.' && 
		(c2 == 't' || c2 == 'T') &&
		(c3 == 't' || c3 == 'T') &&
		(c4 == 'f' || c4 == 'F')
	);
	
	return r;
}


char*
mangle_subfont_ft(char* name, int size){
	char *mangled_name;

	if(name == nil || size == 0)
		return nil;
	
	mangled_name = malloc(256);
	
	if(!mangled_name)
		return nil;

	snprint(mangled_name, 255, "%s[%d]", name, size);

	return mangled_name;
}


Subfont*
readsubfont_ft(Display*d, char *name, int fnt_size, int dolock)
{
	Image *i;
	Rectangle r;

	Fontchar *fc0, *fc;
	Subfont *subfont = nil;

	int sf_x = 0;

	FTfaceinfo finfo;
	FTface ftface;

	FTglyph **aftg;
	int c, cmh, cmw, cma;

	Image **aci;

	char *path = name;	
	char *err;

	char *sf_name;

	err = ftnewface(path, 0, &ftface, &finfo);
	if (err != nil) {
		kwerrstr(err);
		return nil;
	}
#define FNT_CHR_BEG 0
#define FNT_CHR_END finfo.num_glyphs  //255
	
LOGI("font=%s, fnt_sz=%d, num_glyphs=%d", name, fnt_size, FNT_CHR_END);

	err = ftsetcharsize(ftface, fnt_size<<6, 72, 72, &finfo);
	if (err != nil) {
		kwerrstr(err);
		return nil;
	}

	fc = malloc(sizeof(Fontchar)*(FNT_CHR_END-FNT_CHR_BEG+1));
	fc0 = fc;

	aftg = malloc(sizeof(FTglyph*)*(FNT_CHR_END+1-FNT_CHR_BEG));
	memset(aftg, 0, sizeof(FTglyph*)*(FNT_CHR_END+1-FNT_CHR_BEG));

	cmh = finfo.height;
	cma = finfo.ascent;
	cmw = 0; 
	sf_x = 0;

	aci = (Image**)malloc(sizeof(Image**)*(FNT_CHR_END+1-FNT_CHR_BEG));

	for(c = FNT_CHR_BEG; c < FNT_CHR_END+1; c++){
		FTglyph *ftg = malloc(sizeof(FTglyph));
		int j, s1bpr, s2bpr;
		char *err;

		err = ftloadglyph(ftface, c, ftg);
		if (err != nil) {
			kwerrstr(err);
			return nil;
		}

		j = c - FNT_CHR_BEG;
		
		fc[j].x = sf_x;
		fc[j].top = 0; //ftg->top; //
		fc[j].bottom = cmh; //ftg->height; //
		fc[j].left = ftg->left;  // 0; //
		fc[j].width = (ftg->advx + 32) >> 6; //ftg->width; //ftg->bpr + 1; //(ftg->advx + 32) >> 6; //

		aftg[j] = ftg;
		
		sf_x += (ftg->advx + 32) >> 6; //ftg->bpr + 1; //(ftg->advx + 32) >> 6; //ftg->width; //

		s1bpr = ftg->width;
		s2bpr = ftg->bpr;

		r.min.x = 0; r.min.y = 0;
		r.max.x = s2bpr ? s2bpr : (ftg->advx + 32) >> 6; //s2bpr; 
		r.max.y = ftg->height ? ftg->height : cmh;

		aci[j] = allocimage(d, r, GREY8, 0, DBlack); // DTransparent);

		if(ftg->bitmap){
			loadimage(aci[j], r, ftg->bitmap, s2bpr*ftg->height);
		}else{
			char *buf = malloc(r.max.x*r.max.y); //(s2bpr*ftg->height);
			memset(buf, 0xff, r.max.x*r.max.y); //s2bpr*ftg->height);
			loadimage(aci[j], r, buf, r.max.x*r.max.y); //s2bpr*ftg->height);
			free(buf);
		}


	//	if(cmh < ftg->height) 
	//		cmh = ftg->height;
		cmw = sf_x; //+= ftg->width; //ww; //ftg->width; //ftg.advx >> 6; //
	}

	r.min.x = 0;
	r.min.y = 0;
	r.max = r.min;
	r.max.x += cmw;
	r.max.y += cmh;

	i = allocimage(d, r, GREY8, 0, DBlack); //DTransparent);

	sf_x = 0;
	for(c = FNT_CHR_BEG; c < FNT_CHR_END; c++){
		int s1bpr, s2bpr, j = c - FNT_CHR_BEG;
		Image *ci = aci[j];

		FTglyph *ftg = aftg[j];

		s1bpr = ftg->width; //fc[j].width; //
		s2bpr = ftg->bpr;

		r = ci->r;
		r.min.x += fc[j].x;
		r.max.x += r.min.x;

		r.min.y += (cma - ftg->top ); //fc[j].top); 
		r.max.y = r.min.y + ftg->height;
//		r.max.y = cmh - r.min.y;

		draw(i, r, ci, 0, Pt(0, 0) );
		freeimage(ci);

		free(ftg); // ??
		aftg[j] = NULL;
	}
	free(aftg);
	aftg = NULL;
	
	free(aci);
	aci = NULL;
	
	ftdoneface(ftface);

	if(dolock)
		dolock = lockdisplay(d);

	if(dolock)
		unlockdisplay(d);
	if(i == nil)
		return nil;

	if(dolock)
		lockdisplay(d);

	sf_name = mangle_subfont_ft(name, fnt_size);
	subfont = allocsubfont(
				sf_name, 
				FNT_CHR_END-FNT_CHR_BEG, 
				cmh, 
				finfo.ascent, 
				fc, 
				i
	);
	if(sf_name)
		free(sf_name);

	if(dolock)
		unlockdisplay(d);

	if(subfont == nil){
		free(fc);
		return nil;
	}

	return subfont;
}
