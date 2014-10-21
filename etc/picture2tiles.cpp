#include <allegro.h>

#include <sstream>
#include <iostream>
#include <string>


int main(int argc, char **argv)
{
	if(argc != 3)
	{
		std::cout << "pic2tiles: Tileset creation utility\nUsage: pic2tiles <source> <tilesize> <destination>\n";
		return 0;
	}
	allegro_init();
	set_color_depth(32);
	if(argc == 4)
	{
		std::stringstream ss;
		BITMAP *tileset1 = load_bitmap(argv[1], 0);
		int ts;
		ss << argv[2];
		ss >> ts;
		BITMAP *kwijibo = create_bitmap(ts, ts);
		int i = 0;
		for(int y = 0; y < tileset1->h / ts; y++)
		{
			for(int x = 0; x < tileset1->w / ts; x++)
			{
				std::stringstream ss2;
				ss2 << argv[3];
				ss2 << i;
				ss2 << ".bmp";
				blit(tileset1, kwijibo, x * ts, y * ts, 0, 0, ts, ts);
				std::cout << ss2.str().c_str() << '\n';
				save_bitmap(ss2.str().c_str(), kwijibo, 0);
				i++;
			}				
		}		
		destroy_bitmap(tileset1);
	}
	return 0;
}