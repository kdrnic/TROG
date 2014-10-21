#include <allegro.h>
#include <cmath>
#include <iostream>
#include <cstdlib>

int main(int argc, char **argv)
{
	if((argc < 3) || (argc > 6))
	{
		std::cout << "makedoor: Door opening animation creation utility\nUsage: makedoor <image> <destination> (angle1) (angle2) (angle3)\n";
		return 0;
	}
	allegro_init();
	set_color_depth(32);
	BITMAP *src = load_bitmap(argv[1], 0);
	BITMAP *frame = create_bitmap(src->w, src->h);
	BITMAP *sprite = create_bitmap(src->w, src->h * 4);
	draw_sprite(sprite, src, 0, 0);
	float angle[3];
	angle[0] = 4.0 * (M_PI / 16);
	angle[1] = 6.0 * (M_PI / 16);
	angle[2] = 8.0 * (M_PI / 16);
	if(argc >= 4) angle[0] = std::atof(argv[3]);
	if(argc >= 5) angle[1] = std::atof(argv[4]);
	if(argc >= 6) angle[2] = std::atof(argv[5]);
	clear_to_color(sprite, 0xFF00FF);
	clear_to_color(frame, 0xFF00FF);
	for(int x = src->w - 1; x >= 0; x--)
	{
		blit(src, frame, x, 0, int(float(x) * std::cos(angle[0])), 0 - int(float(x) * std::sin(angle[0])), 1, src->h);
	}
	draw_sprite(sprite, frame, 0, src->h);
	clear_to_color(frame, 0xFF00FF);
	for(int x = src->w - 1; x >= 0; x--)
	{
		blit(src, frame, x, 0, int(float(x) * std::cos(angle[1])), 0 - int(float(x) * std::sin(angle[1])), 1, src->h);
	}
	draw_sprite(sprite, frame, 0, src->h * 2);
	clear_to_color(frame, 0xFF00FF);
	for(int x = src->w - 1; x >= 0; x--)
	{
		blit(src, frame, x, 0, int(float(x) * std::cos(angle[2])), 0 - int(float(x) * std::sin(angle[2])), 1, src->h);
	}
	draw_sprite(sprite, frame, 0, src->h * 3);
	save_bitmap(argv[2], sprite, 0);
	return 0;
}