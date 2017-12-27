#include "GargoyleBall.h"
#include "Game.h"

void Gargoyle::BallDied()
{
	ballAlive = false;
}

void Gargoyle::SetParameter(std::string p, std::string v)
{
	if(p == "orientation") orientation = std::atoi(v.c_str());
	else Entity::SetParameter(p, v);
}

void Gargoyle::Update()
{
	if(!ballAlive)
	{
		GargoyleBall *ball = new GargoyleBall(this, orientation);
		game.entitiesManager.Add((Entity *) ball);
		ballAlive = true;
	}
}

Gargoyle::Gargoyle()
{
	sprite = (BITMAP *) game.GetData("spr_gargoyle");
	
	width = 30;
	height = 30;
	offsetX = (49 - width) / 2;
	offsetY = (40 - height) / 2;
	spriteWidth = 49;
	spriteHeight = 40;
	
	frameStart = 0;
	frameEnd = 0;
	inverseSpeed = 1;
	
	ballAlive = false;
}