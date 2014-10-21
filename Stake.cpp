#include "Vampire.h"
#include "Game.h"
#include "Enemy.h"

#include "Stake.h"

BITMAP *Stake::_sprite = 0;

void Stake::Update()
{
	x += speedX;
	y += speedY;
	if(x > 630) alive = false;
	if(x < 0) alive = false;
	if(y < 0) alive = false;
	if(y > 420) alive = false;
	if(MapCollision())
	{
		if(!c) alive = false;
		c = true;
	}
	else c = false;
}

void Stake::OnCollision(Entity *e)
{
	if(e == game.player)
	{
		game.player->OnHit(x, y, width, height, 1);
		alive = false;
		return;
	}
	if(e->Is("VAMPIRE"))
	{
		((Vampire *) e)->OnHit();
		alive = false;
		return;
	}
	if(e->Is("ENEMY"))
	{
		((Enemy *) e)->OnHit(2);
		alive = false;
		return;
	}
	if(e->Is("SOLID")) alive = false;
}

Stake::Stake(int _x, int _y, int o)
{
	if(_sprite == 0) _sprite = load_bitmap("stake.bmp", 0);
	x = _x;
	y = _y;
	orientation = o;
	speedX = speedY = 0;
	int speed = 5;
	switch(o)
	{
		case 0:
			width = 8;
			height = 28;
			speedY = -speed;
			break;
		case 1:
			width = 8;
			height = 28;
			speedY = speed;
			break;
		case 2:
			width = 28;
			height = 8;
			speedX = -speed;
			break;
		case 3:
			width = 28;
			height = 8;
			speedX = speed;
			break;
	}
	spriteWidth = 44;
	spriteHeight = 44;
	offsetX = 8;
	offsetY = 8;
	sprite = _sprite;
	c = MapCollision();
}