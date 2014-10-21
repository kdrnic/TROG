#include <allegro.h>

int main(int argc, char **argv)
{
	allegro_init();
	set_color_depth(32);
	set_gfx_mode(GFX_AUTODETECT_WINDOWED, 640, 480, 0, 0);
	BITMAP *strip = load_bitmap(argv[1], 0);
	char stripOrder[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ.,!?;:'0123456789abcdefghijklmnopqrstuvwxyz%";
	int xAl = 1;
	int yAl = 1;
	BITMAP *allegroFont = load_bitmap(argv[2], 0);
	for(char c = 32; c <= 126; c++)
	{
		int xStrip;
		bool notFound = false;
		for(xStrip = 0; xStrip < 70; xStrip++)
		{
			if(stripOrder[xStrip] == c) break;
			if(xStrip == 69) notFound = true;
		}
		if(notFound)
		{
			xAl += 12;
			if(xAl >= 193)
			{
				xAl = 1;
				yAl += 15;
			}
			continue;
		}
		xStrip *= 11;
		blit(strip, allegroFont, xStrip, 0, xAl, yAl, 11, 14);
		xAl += 12;
		if(xAl >= 193)
		{
			xAl = 1;
			yAl += 15;
		}		
	}
	save_bitmap(argv[3], allegroFont, 0);
	return 0;
}