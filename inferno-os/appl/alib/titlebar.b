implement Titlebar;
include "sys.m";
	sys: Sys;
include "draw.m";
	draw: Draw;
	Point, Rect, Font: import draw;
include "tk.m";
	tk: Tk;
include "titlebar.m";


FONT_TTF : con "/fonts/ttf/Vera.ttf";

h_title := 0;
title_fnt : ref Font;

title_cfg := array[] of {
	"frame .Wm_t -bg #aaaaaa -borderwidth 1",
	"label .Wm_t.title -height ", " -anchor w -bg #aaaaaa -fg white",
#	"button .Wm_t.e -bitmap closebig.bit -command {send wm_title exit} -takefocus 0",
	"button .Wm_t.e -bg #aa2200 -bitmap :", ":window-close.svg -command {send wm_title exit} -takefocus 0",
	"pack .Wm_t.e -side right",
	"bind .Wm_t <Button-1> {send wm_title move %X %Y}",
	"bind .Wm_t <Double-Button-1> {send wm_title lower .}",
	"bind .Wm_t <Motion-Button-1> {}",
	"bind .Wm_t <Motion> {}",
	"bind .Wm_t.title <Button-1> {send wm_title move %X %Y}",
	"bind .Wm_t.title <Double-Button-1> {send wm_title lower .}",
	"bind .Wm_t.title <Motion-Button-1> {}",
	"bind .Wm_t.title <Motion> {}",
	"bind . <FocusIn> {.Wm_t configure -bg #666699;"+
		".Wm_t.title configure -bg #666699;update}",
	"bind . <FocusOut> {.Wm_t configure -bg #aaaaaa;"+
		".Wm_t.title configure -bg #aaaaaa;update}",
};

init()
{
	sys = load Sys Sys->PATH;
	draw = load Draw Draw->PATH;
	tk = load Tk Tk->PATH;
}

new(top: ref Tk->Toplevel, buts: int): chan of string
{
	r := top.screenr;
	h_title = int (r.dy() / 30);


	fnt_csz := int ( h_title * 2/3);
	fnt_nm := FONT_TTF + "_" + string fnt_csz;
	fnt_str := string fnt_csz + " " + string int (fnt_csz * 5/6) + "\n0x0000 0x0fff " + FONT_TTF + "\n";
	fnt := Font.build(top.display, fnt_nm, fnt_str);
#	sys->print("'%s':\n%s ==> %x\n", fnt.name, fnt_str, fnt);
#	fnt_nm = fnt.name;
	title_fnt = fnt;

	
	ctl := chan of string;
	tk->namechan(top, ctl, "wm_title");

	if(buts & Plain)
		return ctl;

	for(i := 0; i < len title_cfg; i++)
		if(i == 1 || i == 3){
			cmd(top, title_cfg[i] + string h_title + title_cfg[i+1] );
			i++;
		}else{
			cmd(top, title_cfg[i]);
		}

	if(buts & OK){
		cmd(top, "button .Wm_t.ok -bg #ffee00 -bitmap :" + string h_title + ":dialog-ok-apply.svg"+   #okbig.bit"+
			" -command {send wm_title ok} -takefocus 0; pack .Wm_t.ok -side left");
		cmd(top, "frame .Wm_t.okf -width 4 -takefocus 0; pack .Wm_t.okf -side left");
	}

	if(buts & Hide){
		cmd(top, "button .Wm_t.top -bg #ffee00 -bitmap :" + string h_title + ":window-minimize.svg"+   #-bitmap minimisebig.bit"+
			" -command {send wm_title task} -takefocus 0; pack .Wm_t.top -side left");
		cmd(top, "frame .Wm_t.topf -width 4 -takefocus 0; pack .Wm_t.topf -side left");
	}

	if(buts & Resize){
		cmd(top, "button .Wm_t.m -bg #ffee00 -bitmap :" + string h_title + ":window-maximize.svg"+   #-bitmap maximisebig.bit"+
			" -command {send wm_title size} -takefocus 0; pack .Wm_t.m -side left");
		cmd(top, "frame .Wm_t.mf -width 4 -takefocus 0; pack .Wm_t.mf -side left");
	}

	if(buts & Help){
		cmd(top, "button .Wm_t.h -bitmap helpbig.bit"+
			" -command {send wm_title help} -takefocus 0; pack .Wm_t.h -side left");
		cmd(top, "frame .Wm_t.hf -width 4 -takefocus 0; pack .Wm_t.hf -side left");
	}

	# pack the title last so it gets clipped first
	cmd(top, "pack .Wm_t.title -side left");
	cmd(top, "pack .Wm_t -fill x");

	return ctl;
}

title(top: ref Tk->Toplevel): string
{
	if(tk->cmd(top, "winfo class .Wm_t.title")[0] != '!')
		return cmd(top, ".Wm_t.title cget -text");
	return nil;
}
	
settitle(top: ref Tk->Toplevel, t: string): string
{
	s := title(top);
	tk->cmd(top, ".Wm_t.title configure -font " + title_fnt.name + " -text '" + t);
	return s;
}

sendctl(top: ref Tk->Toplevel, c: string)
{
	cmd(top, "send wm_title " + c);
}

minsize(top: ref Tk->Toplevel): Point
{
	buts := array[] of {"e", "ok", "top", "m", "h"};
	r := tk->rect(top, ".", Tk->Border);
	r.min.x = r.max.x;
	r.max.y = r.min.y;
	for(i := 0; i < len  buts; i++){
		br := tk->rect(top, ".Wm_t." + buts[i], Tk->Border);
		if(br.dx() > 0)
			r = r.combine(br);
	}
	r.max.x += tk->rect(top, ".Wm_t." + buts[0], Tk->Border).dx();
	return r.size();
}

cmd(top: ref Tk->Toplevel, s: string): string
{
	e := tk->cmd(top, s);
	if (e != nil && e[0] == '!')
		sys->fprint(sys->fildes(2), "wmclient: tk error %s on '%s'\n", e, s);
	return e;
}
