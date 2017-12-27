#include <allegro.h>

#include "Game.h"
#include "Utils.h"

#include "Keys.h"

int main()
{
	srand(time(0));
	allegro_init();
	set_color_depth(32);
	set_gfx_mode(GFX_AUTODETECT_WINDOWED, 640, 480, 0, 0);
	install_keyboard();
	install_mouse();
	install_timer();
	install_joystick(JOY_TYPE_AUTODETECT);
	install_sound(DIGI_AUTODETECT, MIDI_NONE, 0);
	
	LoadControls("controls.cfg");
	
	game.Init();
	game.Start(-1);
	return 0;
}
END_OF_MAIN();
