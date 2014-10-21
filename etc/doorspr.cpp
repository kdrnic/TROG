#include <allegro.h>
#include <string>
#include <iostream>
#include <fstream>

bool fex(std::string n)
{
	std::ifstream f(n.c_str());
	if(f.good())
	{
		f.close();
		return true;
	}
	else
	{
		f.close();
		return false;
	}
}

int main(int argc, char **argv)
{
	if(argc != 3)
	{
		std::cout << "doorspr: Door sprite utility\nUsage: doorspr <source> <dest>\n";
		return 0;
	}
	allegro_init();
	set_color_depth(32);
	BITMAP *src = load_bitmap(argv[1], 0);
	BITMAP *newDest;
	if(fex(argv[2]))
	{
		BITMAP *oldDest;
		oldDest = load_bitmap(argv[2], 0);
		newDest = create_bitmap(60, oldDest->h + 45 * 4);
		clear_to_color(newDest, 0xFF00FF);
		draw_sprite(newDest, oldDest, 0, 0);
		destroy_bitmap(oldDest);
	}
	else
	{
		newDest = create_bitmap(60, 45 * 4);
		clear_to_color(newDest, 0xFF00FF);
	}
	for(int i = 0; i < 4; i++)
	{
		blit(src, newDest, 0, i * (src->h / 4), 30 - (src->w / 2), newDest->h - ((3 - i) * 45) - (src->h / 4), src->w, src->h / 4);
	}
	save_bitmap(argv[2], newDest, 0);
	return 0;
}