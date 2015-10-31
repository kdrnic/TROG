#include "Rat.h"
#include "Game.h"

BITMAP *Rat::_sprite = 0;

bool Rat::Is(std::string what)
{
	if(what == "RAT") return true;
	return HitHurtEnemy::Is(what);
}

void Rat::Update()
{
	walkCounter--;
	if(walkCounter <= 0)
	{
		int newO = rand() % agitation;
		switch(newO)
		{
			case 0:
			case 1:
			case 2:
			case 3:
				orientation = newO;
				walking = true;
				counter = 0;
				break;
			default:
				walking = false;
				break;
		}
		walkCounter = walkTime;
	}
	if(walking)
	{
		frameStart = 0;
		frameEnd = 3;
		switch(orientation)
		{
			case 0:
				MoveSolid(0, -walkSpeed);
				if(GetMinDy() == 0) walkCounter = 0;
				break;
			case 1:
				MoveSolid(0, walkSpeed);
				if(GetMaxDy() == 0) walkCounter = 0;
				break;
			case 2:
				MoveSolid(-walkSpeed, 0);
				if(GetMinDx() == 0) walkCounter = 0;
				break;
			case 3:
				MoveSolid(walkSpeed, 0);
				if(GetMaxDx() == 0) walkCounter = 0;
				break;
		}
	}
	else
	{
		frameStart = 0;
		frameEnd = 0;
	}
	SpriteEntity::Update();
}

SAMPLE *Rat::GetDyingSound()
{
	return (SAMPLE *) game.GetData("snd_rat");
}

Rat::Rat()
{
	if(_sprite == 0) _sprite = (BITMAP *) game.GetData("spr_rat"); // load_bitmap("rat.bmp", 0);
	sprite = _sprite;
	width = 16;
	height = 16;
	offsetX = 8;
	offsetY = 8;
	spriteWidth = 30;
	spriteHeight = 30;
	health = 2;
	hitDamage = 2;
	inverseSpeed = 6;
	frameStart = 0;
	frameEnd = 3;
	walkTime = 45;
	walkSpeed = 1.5;
	walkCounter = 0;
	agitation = 5 + (rand() % 4);
	MoveToFreeSpot(60, 60, 570, 360);
}