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
	SetOrientation(o, speed);
	spriteWidth = 44;
	spriteHeight = 44;
	offsetX = 8;
	offsetY = 8;
	damage = 2;
}