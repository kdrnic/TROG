#include <allegro.h>

#include "Game.h"
#include "Utils.h"

#include "Keys.h"

void SwitchOut()
{
}

int main()
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
	set_display_switch_callback(SWITCH_OUT, &SwitchOut);

	LoadControls();

	game.Init();
	game.Start(-1);
	return 0;
}
END_OF_MAIN();
