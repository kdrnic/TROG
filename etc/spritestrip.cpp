#include <allegro.h>

#include <iostream>
#include <sstream>

//#include "Map.h"

int main(int argc, char **argv)
{
	if(argc != 5)
	{
		std::cout << "spritestrip: Sprite reorientation utility\nUsage: spritestrip <sprite> <size> <destination> [HORIZONTAL/VERTICAL]\n";
	}
	allegro_init();
	set_color_depth(32);
	if(argc == 5)
	{
		std::stringstream ss;
		BITMAP *tileset1 = load_bitmap(argv[1], 0);
		int ts;
		ss << argv[2];
		ss >> ts;
		BITMAP *tileset2;
		if(std::string(argv[4]) == "HORIZONTAL")
		{
			tileset2 = create_bitmap(tileset1->w * (tileset1->h / ts), ts);
			for(int i = 0; i < tileset1->h / ts; i++)
			{
				blit(tileset1, tileset2, 0, i * ts, i * tileset1->w, 0, tileset1->w, ts); 
			}
		}
		else if(std::string(argv[4]) == "VERTICAL")
		{
			tileset2 = create_bitmap(ts, ((tileset1->w * tileset1->h) / (ts * ts)) * ts);
			for(int y = 0; y < tileset1->h / ts; y++)
			{
				for(int x = 0; x < tileset1->w / ts; x++)
				{
					blit(tileset1, tileset2, x * ts, y * ts, 0, (tileset1->w * y) + (ts * x), ts, ts); 
				}				
			}
		}
		else
		{
			destroy_bitmap(tileset1);
			return 0;
		}
		save_bitmap(argv[3], tileset2, 0);
		destroy_bitmap(tileset1);
		destroy_bitmap(tileset2);
	}
	return 0;
}