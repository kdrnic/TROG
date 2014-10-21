#include "Poof.h"

BITMAP *Poof::_sprite = 0;

void Poof::Update()
{
	SpriteEntity::Update();
	if(frame == 4)
	{
		alive = false;
	}
}

Poof::Poof(int _x, int _y, int o)
{
	if(_sprite == 0) _sprite = load_bitmap("poof.bmp", 0);
	x = _x - 14;
	y = _y - 14;
	width = 30;
	height = 30;
	spriteWidth = 30;
	spriteHeight = 30;
	frameEnd = 7;
	offsetX = 0;
	offsetY = 0;
	inverseSpeed = 4 + o * 1;
	sprite = _sprite;
	layer = 2;
	orientation = o;
	counter = 0;
}