#include "BarbedWire.h"
#include "Game.h"

BITMAP *BarbedWire::_sprite = 0;

BarbedWire::BarbedWire()
{
	width = 30;
	height = 30;			
	spriteWidth = 31;
	spriteHeight = 30;
	if(_sprite == 0) _sprite = (BITMAP *) game.GetData("spr_barbedWire"); // load_bitmap("barbedWire.bmp", 0);
	sprite = _sprite;
	health = 2;
	hitDamage = 1;
	MoveToFreeSpot(60, 60, 570, 360);
}

Entity *BarbedWire::Create()
{
	return new BarbedWire;
}