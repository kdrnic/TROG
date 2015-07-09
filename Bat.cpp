#include "Bat.h"
#include "Game.h"

BITMAP *Bat::_sprite = 0;

bool Bat::Is(std::string what)
{
	if(what == "BAT") return true;
	return HitHurtEnemy::Is(what);
}

void Bat::Update()
{
	float newDx = dx;
	float newDy = dy;
	if(dx > 0)
	{
		if((GetMaxDx() < dx) || (x + dx + width > 630)) newDx *= -1;
	}
	else
	{
		if((GetMinDx() > dx) || (x + dx < 0)) newDx *= -1;
	}
	if(dy > 0)
	{
		if((GetMaxDy() < dy) || (y + dy + width > 420)) newDy *= -1;
	}
	else
	{
		if((GetMinDy() > dy) || (y + dx < 0)) newDy *= -1;
	}
	MoveSolid(dx, dy);
	dx = newDx;
	dy = newDy;
	if(dy > 0) orientation = 0;
	else orientation = 1;
	SpriteEntity::Update();
}

Bat::Bat()
{
	if(_sprite == 0) _sprite = (BITMAP *) game.GetData("spr_bat"); // load_bitmap("bat.bmp", 0);
	sprite = _sprite;
	dx = 4.0 / 3.0;
	dy = 1.0;
	if(rand() % 2) dx *= -1;
	if(rand() % 2) dy *= -1;
	width = 16;
	height = 12;
	offsetX = 7;
	offsetY = 7;
	spriteWidth = 30;
	spriteHeight = 30;
	health = 2;
	hitDamage = 2;
	inverseSpeed = 5;
	frameStart = 0;
	frameEnd = 3;
	MoveToFreeSpot(60, 60, 570, 360);
}

Bat::Bat(int _x, int _y)
{
	if(_sprite == 0) _sprite = (BITMAP *) game.GetData("spr_bat"); // load_bitmap("bat.bmp", 0);
	sprite = _sprite;
	dx = 4.0 / 3.0;
	dy = 1.0;
	if(rand() % 2) dx *= -1;
	if(rand() % 2) dy *= -1;
	width = 16;
	height = 12;
	offsetX = 7;
	offsetY = 7;
	spriteWidth = 30;
	spriteHeight = 30;
	health = 2;
	hitDamage = 2;
	inverseSpeed = 5;
	frameStart = 0;
	frameEnd = 3;
	x = _x - width / 2;
	y = _y - height / 2;
}