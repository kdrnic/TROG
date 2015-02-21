#include "Game.h"
#include "ZombieHole.h"

ZombieHole::ZombieHole(int _x, int _y)
{
	x = _x;
	y = _y;
	sprite = (BITMAP *) game.GetData("spr_hole");
	width = 20;
	height = 20;
	spriteWidth = 30;
	spriteHeight = 30;
	offsetX = 5;
	offsetY = 10;
	frameStart = frameEnd = 0;
	inverseSpeed = 60;
	layer = -2;
	orientation = 0;
	counter = 0;
}