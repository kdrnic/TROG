#include <allegro.h>
#include <iostream>

int main(int argc, char **argv)
{
	if(argc != 4)
	{
		std::cout << "spriteCentralizer: Hitbox selection utility\nUsage: spriteCentralizer <sprite> <framewidth> <frameheight>\n";
	}
	allegro_init();
	set_color_depth(32);
	set_gfx_mode(GFX_AUTODETECT_WINDOWED, 640, 480, 0, 0);
	install_keyboard();
	if(argc != 4) return 0;
	BITMAP *sprite = load_bitmap(argv[1], 0);
	int frameW = atoi(argv[2]);
	int frameH = atoi(argv[3]);
	int *frameDx = new int[sprite->w / frameW];
	int *frameDy = new int[sprite->h / frameH];
	for(int i = 0; i < sprite->w / frameW; i++) frameDx[i] = 0;
	for(int i = 0; i < sprite->h / frameH; i++) frameDy[i] = 0;
	int newFrameW = frameW;
	int newFrameH = frameH;
	int boxW = frameW;
	int boxH = frameH;
	int offX = 0;
	int offY = 0;
	BITMAP *db = create_bitmap(640, 480);
	while(!key[KEY_ESC])
	{
		if(key[KEY_LEFT] && (offX > 0)) offX--;
		if(key[KEY_RIGHT] && (offX + boxW < frameW)) offX++;
		if(key[KEY_UP] && (offY > 0)) offY--;
		if(key[KEY_DOWN] && (offY + boxH < frameH)) offY++;
		
		if(key[KEY_A] && (boxW > 0)) boxW--;
		if(key[KEY_D] && (offX + boxW < frameW)) boxW++;
		if(key[KEY_W] && (boxH > 0)) boxH--;
		if(key[KEY_S] && (offY + boxH < frameH)) boxH++;
		
		clear(db);
		rectfill(db, 0, 0, sprite->w, sprite->h, 0xFF01FF);
		draw_sprite(db, sprite, 0, 0);
		for(int c = 0; c < sprite->w / frameW; c++)
		{
			for(int r = 0; r < sprite->h / frameH; r++)
			{
				rect(db, (c * frameW) + offX, (r * frameH) + offY, (c * frameW) + offX + boxW - 1, (r * frameH) + offY + boxH - 1, 0xFF0000);
			}
		}
		textprintf_ex(db, font, 0, 471, 0xFFFFFF, 0, "offX %d offY %d boxW %d boxH %d", offX, offY, boxW, boxH);
		draw_sprite(screen, db, 0, 0);
		rest(30);
	}
	return 0;
}