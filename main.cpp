#include <allegro.h>

#include "Game.h"
#include "Utils.h"

int main()
{
	srand(time(0));
	allegro_init();
	set_color_depth(32);
	set_gfx_mode(GFX_AUTODETECT_WINDOWED, 640, 480, 0, 0);
	install_keyboard();
	install_mouse();
	install_timer();
	game.Init();
	game.Start(-1);
	return 0;
}
END_OF_MAIN();
