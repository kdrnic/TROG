#include <allegro.h>
#include <cstdlib>
#include <iostream>

int main(int argc, char **argv)
{
	if(argc != 8)
	{
		std::cout << "animview: Animation preview utility\nUsage: animview <sprite> <framewidth> <frameheight> <start> <finnish> <orientation> <speed>\n";
		return 0;
	}
	allegro_init();
	set_color_depth(32);
	set_gfx_mode(GFX_AUTODETECT_WINDOWED, 640, 480, 0, 0);
	install_mouse();
	install_keyboard();
	install_timer();
	BITMAP *sprite = load_bitmap(argv[1], 0);
	int spriteWidth = std::atoi(argv[2]);
	int spriteHeight = std::atoi(argv[3]);
	int frameStart = std::atoi(argv[4]);
	int frameEnd = std::atoi(argv[5]);
	int orientation = std::atoi(argv[6]);
	int inverseSpeed = std::atoi(argv[7]);
	BITMAP *db = create_bitmap(640, 480);
	int frame;
	int counter = 0;
	int offsetX = 0;
	int offsetY = 0;
	int x = 320;
	int y = 240;
	while(!key[KEY_ESC])
	{
		clear(db);
		counter++;
		frame = frameStart + ((counter / inverseSpeed) % (frameEnd - frameStart + 1));
		masked_blit(sprite, db, orientation * spriteWidth, frame * spriteHeight, x - offsetX, y - offsetY, spriteWidth, spriteHeight);
		draw_sprite(screen, db, 0, 0);
		rest(18);
	}
	return 0;
}