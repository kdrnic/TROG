#include <allegro.h>

#include "Game.h"
#include "Utils.h"

#include "Keys.h"
/*
DIALOG cfgDialog[] =
{
//	(dialog proc)		(x)		(y)		(w)		(h)		(fg)	(bg)	(key)	(flags)		(d1)					(d2)	(dp)				(dp2)	(dp3)
	{d_clear_proc,		0,		0,		0,		0,		WHITE,	0,		0,		0,			0,						0,		NULL,				NULL,	NULL	},//0
	{d_rtext_proc,		96,		32,		0,		0,		WHITE,	0,		0,		0,			0,						0,		"Address:",			0,		0		},//1
	{d_edit_proc,		96,		32,		224,	8,		WHITE,	0,		0,		0,			sizeof(address)-1,		0,		address,			NULL,	NULL	},//2
	{d_radio_proc,		320,	32,		160,	16,		WHITE,	0,		0,		D_SELECTED,	0,						0,		"Server",			0,		0		},//3
	{d_radio_proc,		480,	32,		160,	16,		WHITE,	0,		0,		0,			0,						0,		"Client",			0,		0		},//4
	{d_button_proc,		80,		64,		160,	16,		WHITE,	0,		0,		D_EXIT,		0,						0,		"Connect/Listen",	NULL,	NULL	},//5
	{d_ctext_proc,		320,	8,		0,		0,		WHITE,	0,		0,		0,			0,						0,		status,				0,		0		},//6
	{d_list_proc,		340,	64,		280,	64,		WHITE,	0,		0,		D_EXIT,		1,						0,		driverlist_getter,	0,		0		},//7
	{d_textbox_proc,	16,		136,	608,	96,		WHITE,	0,		0,		D_SELECTED,	0,						0,		logp_buffer,		0,		0		},//8
	{update_proc,		0,		0,		0,		0,		0,		0,		0,		0,			0,						0,		0,					0,		0		},//9
	{d_edit_proc,		96,		48,		224,	16,		WHITE,	0,		0,		0,			sizeof(name)-1,			0,		name,				0,		0		},//10
	{d_rtext_proc,		96,		48,		0,		0,		WHITE,	0,		0,		0,			0,						0,		"Client name:",		0,		0		},//11
	{d_button_proc,		16,		240,	160,	16,		WHITE,	0,		0,		D_EXIT,		0,						0,		"Click me",			0,		0		},//12
	{d_text_proc,		128,	96,		0,		0,		WHITE,	0,		0,		0,			0,						0,		str_mrec,			0,		0		},//13
	{d_rtext_proc,		128,	96,		0,		0,		WHITE,	0,		0,		0,			0,						0,		"Msgs. received:",	0,		0		},//14
	{d_text_proc,		128,	104,	0,		0,		WHITE,	0,		0,		0,			0,						0,		str_msnt,			0,		0		},//15
	{d_rtext_proc,		128,	104,	0,		0,		WHITE,	0,		0,		0,			0,						0,		"Msgs. sent:",		0,		0		},//16
	{d_bitmap_proc,		16, 	272, 	608,	96,		WHITE,	0,		0,		0,			0,						0,		0,					0,		0,		},//17
	{d_button_proc,		320,	240,	160,	16,		WHITE,	0,		0,		D_EXIT,		0,						0,		"Clear buffer",		0,		0		},//18
	{d_button_proc,		16,		376,	160,	16,		WHITE,	0,		0,		D_EXIT,		0,						0,		"Send RESET",		0,		0		},//19
	{d_check_proc,		320,	376,	160,	16,		WHITE,	0,		0,		D_SELECTED,	1,						0,		"Send time msgs.",	0,		0		},//20
	{d_edit_proc,		16,		400,	464,	8,		WHITE,	0,		0,		0,			sizeof(chat_string)-1,	0,		chat_string,		0,		0		},//21
	{d_button_proc,		496,	400,	128,	16,		WHITE,	0,		0,		D_EXIT,		0,						0,		"Send",				0,		0		},//22
	{NULL,				0,		0,		0,		0,		0,		0,		0,		0,			0,						0,		NULL,				NULL,	NULL	}
};
*/
void ConfigurationOptions()
{
}

void SwitchOut()
{
	game.shallPause = true;
}

int main(int argc, char **argv)
{
	bool fullScreen;
	int windowW, windowH;

	srand(time(0));
	allegro_init();
	set_color_depth(32);

	set_config_file("trog.cfg");
	fullScreen = get_config_int("gfxmode", "fullscreen", 0);
	windowW = get_config_int("gfxmode", "width", 640);
	windowH = get_config_int("gfxmode", "height", 480);

	set_gfx_mode(fullScreen ? GFX_AUTODETECT_FULLSCREEN : GFX_AUTODETECT_WINDOWED, windowW, windowH, 0, 0);
	install_keyboard();
	install_mouse();
	install_timer();
	install_joystick(JOY_TYPE_AUTODETECT);
	install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, 0);

	set_window_title("The Revenge of Gregorius");
	set_display_switch_mode(SWITCH_BACKGROUND);
	set_display_switch_callback(SWITCH_OUT, &SwitchOut);

	LoadControls();

	game.Init();
	game.Start(-1);
	return 0;
}
END_OF_MAIN();
