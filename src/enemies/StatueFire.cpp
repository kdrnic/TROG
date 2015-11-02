#include "Utils.h"
#include "Game.h"

#include "StatueFire.h"

void StatueFire::OnSolid(Entity *e)
{
}

StatueFire::StatueFire()
{
	sprite = (BITMAP *) game.GetData("spr_statueFire");
	width = 5;
	height = 8;
	spriteWidth = 33;
	spriteHeight = 46;
	offsetX = 14;
	offsetY = 38;
	damage = 2;
	inverseSpeed = 5;
	frameStart = 0;
	frameEnd = 3;	
}