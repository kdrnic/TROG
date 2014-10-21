#include <allegro.h>

int orientation;
void Orientate(float dx, float dy)
{
	if(dx == 0)
	{
		if(dy < 0) orientation = 0;
		if(dy > 0) orientation = 1;
	}
	else
	{
		float ratio;
		if(dx < 0) ratio = dy / (0 - dx);
		else ratio = dy / dx;
		if(ratio <= -0.5) orientation = 0;
		else if(ratio >= 0.5) orientation = 1;		
		else if(dx > 0) orientation = 3;
		else orientation = 2;
	}
}

int main()
{
	allegro_init();
	set_color_depth(32);
	set_gfx_mode(GFX_AUTODETECT_FULLSCREEN, 640, 480, 0, 0);
	install_keyboard();
	install_mouse();
	install_timer();
	int x = 0, y = 0;
	orientation = 0;
	int omx, omy;
	while(!key[KEY_ESC])
	{
		int ox = x, oy = y, oo = orientation;
		if(mouse_b & 2) x = mouse_x;
		if(mouse_b & 2) y = mouse_y;
		Orientate(mouse_x - x, mouse_y - y);
		switch(oo)
		{
			case 0:
				vline(screen, ox, oy, oy - 10, 0);
				break;
			case 1:
				vline(screen, ox, oy, oy + 10, 0);
				break;
			case 2:
				hline(screen, ox, oy, ox - 10, 0);
				break;
			case 3:
				hline(screen, ox, oy, ox + 10, 0);
				break;
		}
		switch(orientation)
		{
			case 0:
				vline(screen, x, y, y - 10, 0xFF00);
				break;
			case 1:
				vline(screen, x, y, y + 10, 0xFF00);
				break;
			case 2:
				hline(screen, x, y, x - 10, 0xFF00);
				break;
			case 3:
				hline(screen, x, y, x + 10, 0xFF00);
				break;
		}
		putpixel(screen, x, y, 255);
		putpixel(screen, omx, omy, 0);
		omx = mouse_x;
		omy = mouse_y;		
		putpixel(screen, mouse_x, mouse_y, 0xFFFF00);		
	}
	return 0;
}