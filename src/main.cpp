#include <allegro.h>

#include "Game.h"
#include "Utils.h"

#include "Keys.h"

#include <cstring>
#include <iostream>

#define WHITE 0xFFFFFF

bool availableMIDIs[3];
int numMIDIs;

void CheckMIDIs()
{
	availableMIDIs[0] = detect_midi_driver(MIDI_NONE) != 0;
	availableMIDIs[1] = detect_midi_driver(MIDI_AUTODETECT) != 0;
	availableMIDIs[2] = detect_midi_driver(MIDI_DIGMID) != 0;
	numMIDIs = (availableMIDIs[0]) + (availableMIDIs[1]) + (availableMIDIs[2]);
}

const char *MIDIDriverGetter_names[] =
{
	"None (no music)",
	"Default OS driver",
	"Allegro synth (uses patches.dat)"
};

char *MIDIDriverGetter(int index, int *list_size)
{
	char **names = (char **) MIDIDriverGetter_names;
	if(index < 0)
	{
		*list_size = numMIDIs;
		return 0;
	}
	else
	{
		if(numMIDIs < 3)
		{
			if(index == 0)
			{
				if(availableMIDIs[0]) return (char *) names[0];
				if(availableMIDIs[1]) return (char *) names[0];
				if(availableMIDIs[2]) return (char *) names[0];
				return 0;
			}
			if(index == 1)
			{
				if(availableMIDIs[0])
				{
					if(availableMIDIs[1]) return (char *) names[0];
					if(availableMIDIs[2]) return (char *) names[0];
					return 0;
				}
				if(availableMIDIs[1])
				{
					if(availableMIDIs[2]) return (char *) names[0];
					return 0;
				}
				return 0;
			}
			if(index == 3)
			{
				if(availableMIDIs[2]) return (char *) names[0];
				return 0;
			}
		}
		else
		{
			return (char *) names[index];
		}
	}
	return names[0];
}

char *JoystickGetter(int index, int *list_size)
{
	const char *names[] =
	{
		"Joystick #1",
		"Joystick #2",
		"Joystick #3",
		"Joystick #4",
		"Joystick #5",
		"Joystick #6",
		"Joystick #7",
		"Joystick #8",
		"Joystick #9",
		"Joystick #10",
		"Joystick #11",
		"Joystick #12",
		"Joystick #13",
		"Joystick #14",
		"Joystick #15",
		"Joystick #16"
	};
	if(index < 0)
	{
		*list_size = num_joysticks;
		return 0;
	}
	else return (char *) names[index];
}

char cfgW[5] = "", cfgH[5] = "";
bool cfgFull, cfgZoom;

DIALOG cfgDialog[] =
{
//	(dialog proc)		(x)		(y)		(w)		(h)		(fg)	(bg)	(key)	(flags)		(d1)					(d2)	(dp)									(dp2)			(dp3)
	{d_clear_proc,		0,		0,		0,		0,		WHITE,	0,		0,		0,			0,						0,		(void *)0,								(void *) 0,		(void *) 0		},//0
	{d_check_proc,		320,	16,		160,	16,		WHITE,	0,		0,		0,			1,						0,		(void *)"Fullscreen",					(void *) 0,		(void *) 0		},//1
	{d_check_proc,		320,	32,		160,	16,		WHITE,	0,		0,		0,			1,						0,		(void *)"Zoom in (2X)",					(void *) 0,		(void *) 0		},//2
	{d_list_proc,		320,	48,		280,	48,		WHITE,	0,		0,		0,			0,						0,		(void *)MIDIDriverGetter,				(void *) 0,		(void *) 0		},//3
	{d_button_proc,		60,		464,	200,	16,		WHITE,	0,		0,		D_EXIT,		0,						0,		(void *)"Apply and save",				(void *) 0,		(void *) 0		},//4
	{d_button_proc,		380,	464,	200,	16,		WHITE,	0,		0,		D_EXIT,		0,						0,		(void *)"Leave (without saving)",		(void *) 0,		(void *) 0		},//5
	{d_button_proc,		60,		224,	200,	16,		WHITE,	0,		0,		D_EXIT,		0,						0,		(void *)"Configure keyboard input",		(void *) 0,		(void *) 0		},//6
	{d_button_proc,		380,	224,	200,	16,		WHITE,	0,		0,		D_EXIT,		0,						0,		(void *)"Configure joystick input",		(void *) 0,		(void *) 0		},//7
	{d_list_proc,		320,	112,	280,	48,		WHITE,	0,		0,		0,			0,						0,		(void *)JoystickGetter,					(void *) 0,		(void *) 0		},//8
	{d_rtext_proc,		320,	112,	0,		0,		WHITE,	0,		0,		0,			0,						0,		(void *)"Joystick select:",				(void *) 0,		(void *) 0		},//9
	{d_edit_proc,		320,	192,	224,	8,		WHITE,	0,		0,		0,			sizeof(cfgW)-1,			0,		(void *)cfgW,							(void *) NULL,	(void *) NULL	},//10
	{d_edit_proc,		320,	208,	224,	8,		WHITE,	0,		0,		0,			sizeof(cfgH)-1,			0,		(void *)cfgH,							(void *) NULL,	(void *) NULL	},//11
	{d_rtext_proc,		320,	192,	0,		0,		WHITE,	0,		0,		0,			0,						0,		(void *)"Screen/window width:",			(void *) 0,		(void *) 0		},//12
	{d_rtext_proc,		320,	208,	0,		0,		WHITE,	0,		0,		0,			0,						0,		(void *)"Screen/window height:",		(void *) 0,		(void *) 0		},//13
	{d_rtext_proc,		320,	48,		0,		0,		WHITE,	0,		0,		0,			0,						0,		(void *)"MIDI Driver:",					(void *) 0,		(void *) 0		},//14
	{d_ctext_proc,		320,	0,		0,		0,		WHITE,	0,		0,		0,			0,						0,		(void *)"CONFIGURATION",				(void *) 0,		(void *) 0		},//15
	{d_button_proc,		380,	432,	200,	16,		WHITE,	0,		0,		D_EXIT,		0,						0,		(void *)"Restore default and leave",	(void *) 0,		(void *) 0		},//16
	{NULL,				0,		0,		0,		0,		0,		0,		0,		0,			0,						0,		(void *)0,					(void *) 0,		(void *) 0	}
};

void CfgLoad()
{
	std::strcpy(cfgW, Itoa(get_config_int("gfxmode", "width", 640)).c_str());
	std::strcpy(cfgH, Itoa(get_config_int("gfxmode", "height", 480)).c_str());
	cfgFull = get_config_int("gfxmode", "fullscreen", 0);
	cfgZoom = get_config_int("gfxmode", "zoomin", 0);
	LoadControls();
}

void CfgSave()
{
	set_config_int("gfxmode", "fullscreen", cfgFull);
	set_config_int("gfxmode", "zoomin", cfgZoom);

	set_config_int("gfxmode", "width", std::atoi(cfgW));
	set_config_int("gfxmode", "height", std::atoi(cfgH));

	SaveControls();
}

void CfgApply()
{
	bool resGood = true;
	for(int i = 0; i < 4; i++)
	{
		if((i < strlen(cfgW)) && ((cfgW[i] > '9') || (cfgW[i] < '0'))) resGood = false;
		if((i < strlen(cfgH)) && ((cfgH[i] > '9') || (cfgH[i] < '0'))) resGood = false;
	}
	if(!resGood)
	{
		strcpy(cfgW, "640");
		strcpy(cfgH, "480");
	}

	cfgFull = (cfgDialog[1].flags & D_SELECTED) && true;
	cfgZoom = (cfgDialog[2].flags & D_SELECTED) && true;
}

void CfgKb()
{
}

void CfgJoy()
{
}

void CfgDefaults()
{
}

void DoConfiguration()
{
	std::cout << numMIDIs;
	LoadControls();
	
	if(cfgFull) cfgDialog[1].flags |= D_SELECTED;
	if(cfgZoom) cfgDialog[2].flags |= D_SELECTED;

	int ret;
	while((ret = do_dialog(cfgDialog, -1)) != 5)
	{
		switch(ret)
		{
			case 4:		//apply
				CfgApply();
				if((screen->w != std::atoi(cfgW)) || (screen->h != std::atoi(cfgH)))
				{
					if(!set_gfx_mode(cfgFull ? GFX_AUTODETECT_FULLSCREEN : GFX_AUTODETECT_WINDOWED, std::atoi(cfgW), std::atoi(cfgH), 0, 0))
					{
						if(alert("Keep this graphics mode?", "If not, configuration won't be saved", "", "Yes", "No", 0, 0) == 1) CfgSave();
						else
						{
							strcpy(cfgW, "640");
							strcpy(cfgH, "480");
							set_gfx_mode(cfgFull ? GFX_AUTODETECT_FULLSCREEN : GFX_AUTODETECT_WINDOWED, std::atoi(cfgW), std::atoi(cfgH), 0, 0);
						}
					}
					else
					{
						strcpy(cfgW, "640");
						strcpy(cfgH, "480");
						set_gfx_mode(cfgFull ? GFX_AUTODETECT_FULLSCREEN : GFX_AUTODETECT_WINDOWED, std::atoi(cfgW), std::atoi(cfgH), 0, 0);
					}
				}
				break;
			case 5:		//leave
				break;
			case 6:		//kb
				CfgKb();
				break;
			case 7:		//joy
				CfgJoy();
				break;
			case 16:	//leave default
				CfgDefaults();
				break;
		}
	}
}

void SwitchOut()
{
	game.shallPause = true;
}

void SwitchIn()
{
	game.updateFiles = true;
}

int MainMenu()
{
	clear(screen);

	const char *strings[] = {"PLAY", "OPTIONS", "QUIT"};
	int colorSel = 0xFFFF00;
	int colorNot = 0xFFFFFF;

	int i;
	int y;
	int sel = 0;

	while(true)
	{
		for(i = 0, y = screen->h / 4; i < 3; i++, y += screen->h / 4)
		{
			textout_centre_ex(screen, font, strings[i], 320, y, (i == sel) ? colorSel : colorNot, 0);
		}
		UpdateKeys();
		if(upKey == KeyDown) sel = (sel + 2) % 3;
		if(downKey == KeyDown) sel = (sel + 1) % 3;

		if((aKey == KeyDown) || (sKey == KeyDown) || (xKey == KeyDown) || (cKey == KeyDown)) return sel;
	}
}

int main(int argc, char **argv)
{
	srand(time(0));
	allegro_init();

	install_keyboard();
	install_mouse();
	install_timer();
	install_joystick(JOY_TYPE_AUTODETECT);

	set_color_depth(32);

	CheckMIDIs();
	set_config_file("trog.cfg");

	CfgLoad();

	set_gfx_mode(cfgFull ? GFX_AUTODETECT_FULLSCREEN : GFX_AUTODETECT_WINDOWED, std::atoi(cfgW), std::atoi(cfgH), 0, 0);
	install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, 0);

	set_window_title("The Revenge of Gregorius");
	set_display_switch_mode(SWITCH_BACKGROUND);
	set_display_switch_callback(SWITCH_OUT, &SwitchOut);
	set_display_switch_callback(SWITCH_IN, &SwitchIn);
	
	game.Init();

	bool notQuit = true;
	while(notQuit)
	{
		int ret = MainMenu();
		switch(ret)
		{
			case 0:
				game.zoomMode = cfgZoom;
				game.Start(-1);
				break;
			case 1:
				DoConfiguration();
				break;
			case 2:
				notQuit = false;
				break;
		}
	}
	return 0;
}
END_OF_MAIN();
