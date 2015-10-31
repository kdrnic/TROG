#include "Vampire.h"
#include "Game.h"
#include "Enemy.h"

#include "Stake.h"

Stake::Stake(int _x, int _y, int o)
{
	sprite = (BITMAP *) game.GetData("spr_stake");
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
	damage = 2;
}