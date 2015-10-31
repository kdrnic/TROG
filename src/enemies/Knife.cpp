#include "Utils.h"
#include "Game.h"

#include "Knife.h"

Knife::Knife()
{
	sprite = (BITMAP *) game.GetData("spr_knife");
	width = 3;
	height = 3;
	spriteWidth = 15;
	spriteHeight = 15;
	offsetX = 6;
	offsetY = 6;
	damage = 2;
	inverseSpeed = 3;
	frameStart = 0;
	frameEnd = 3;	
}