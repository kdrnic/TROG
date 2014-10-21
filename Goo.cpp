#include "Goo.h"

BITMAP *Goo::_sprite = 0;

void Goo::Update()
{
	SpriteEntity::Update();
	if(frame == 4)
	{
		alive = false;
	}
}

Goo::Goo(int _x, int _y, int o)
{
	if(_sprite == 0) _sprite = load_bitmap("goo.bmp", 0);
	x = _x - 14;
	y = _y - 14;
	width = 30;
	height = 30;
	spriteWidth = 30;
	spriteHeight = 30;
	frameEnd = 7;
	offsetX = 0;
	offsetY = 0;
	inverseSpeed = 60;
	sprite = _sprite;
	layer = -2;
	orientation = o;
	counter = 0;
}