#include <cmath>

#include "Game.h"
#include "Bat.h"
#include "Poof.h"

#include "Vampire.h"

BITMAP *Vampire::_sprite = 0;

float MinAbs(float a, float b)
{
	if(std::fabs(a) < std::fabs(b)) return a;
	return b;
}

void Vampire::Draw(BITMAP *bmp)
{
	if(state != 2) SpriteEntity::Draw(bmp);
	if((blinkingCounter <= 0) || (((blinkingCounter - (blinkingCounter % (30 / blinkingHz))) / (30 / blinkingHz)) % 2 == 0)) SpriteEntity::Draw(bmp);
}

bool Vampire::Is(std::string what)
{
	if(what == "SOLID") return true;
	if(what == "VAMPIRE") return true;
	return Entity::Is(what);
}

bool Vampire::IsEntitySolid(Entity *e)
{
	if(e->Is("BAT")) return false;
	return Entity::IsEntitySolid(e);
}

void Vampire::Update()
{
	SpriteEntity::Update();
	int distance2 = ((game.player->x - x) * (game.player->x - x)) + ((game.player->y - y) * (game.player->y - y));
	if(state == 0)
	{
		if(distance2 < wakingDistance * wakingDistance)
		{
			state = 1;
			frameEnd = 8;
			counter = 0;
			inverseSpeed = wakingSpeed;
		}
	}
	if(state == 1)
	{
		if(frame == 8)
		{
			state = 2;
			frameStart = 8;
			frameEnd = 11;
			inverseSpeed = animSpeed;
			destX = minX + (rand() % (maxX - minX));
			destY = minY + (rand() % (maxY - minY));
		}
	}
	if(state == 2)
	{
		int dx = destX - x;
		int dy = destY - y;
		if(axis)
		{
			if(dx < 0)
			{
				orientation = 2;
				MoveSolid(MinAbs(-speed, dx), 0);
			}
			else if(dx > 0)
			{
				orientation = 3;
				MoveSolid(MinAbs(speed, dx), 0);
			}
			else if(dy < 0)
			{
				orientation = 0;
				MoveSolid(0, MinAbs(-speed, dy));
			}
			else if(dy > 0)
			{
				orientation = 1;
				MoveSolid(0, MinAbs(speed, dy));
			}
		}
		else
		{
			if(dy < 0)
			{
				orientation = 0;
				MoveSolid(0, MinAbs(-speed, dy));
			}
			else if(dy > 0)
			{
				orientation = 1;
				MoveSolid(0, MinAbs(speed, dy));
			}
			else if(dx < 0)
			{
				orientation = 2;
				MoveSolid(MinAbs(-speed, dx), 0);
			}
			else if(dx > 0)
			{
				orientation = 3;
				MoveSolid(MinAbs(speed, dx), 0);
			}
		}
		if((x == destX) && (y == destY))
		{
			destX = minX + (rand() % (maxX - minX));
			destY = minY + (rand() % (maxY - minY));
			axis = !axis;
		}
		if(distance2 < teleportDistance * teleportDistance)
		{
			Entity *poof = new Poof(x + width / 2, y + height / 2);
			game.entitiesManager.Add(poof);
			x = minX + (rand() % (maxX - minX));
			y = minY + (rand() % (maxY - minY));
			destX = minX + (rand() % (maxX - minX));
			destY = minY + (rand() % (maxY - minY));
			axis = !axis;
		}
		
		batCounter++;
		if(batCounter > batTime)
		{
			if(game.entitiesManager.Count("BAT") < maxBats)
			{
				Entity *bat = new Bat(x + width / 2, y + height / 2);
				game.entitiesManager.Add(bat);
				batCounter = 0;
			}
		}
		
		if(health < 0)
		{
			state = 3;
			counter = 0;
			frameStart = frameEnd = 8;
			dieCountdown = dieTime;
		}
		blinkingCounter--;
	}
	if(state == 3)
	{
		if(game.frame % diePoofDelay == 0)
		{
			Entity *poof = new Poof(x + rand() % int(width), y + rand() % int(height));
			game.entitiesManager.Add(poof);
		}
		dieCountdown--;
		if(dieCountdown < 0)
		{
			Entity *poof = new Poof(x + width / 2, y + height / 2);
			game.entitiesManager.Add(poof);
			game.SetQuestState("vampire", "defeated");
			alive = false;
		}
	}
}

void Vampire::OnHit()
{
	if(state != 2) return;
	if(blinkingCounter <= 0)
	{
		health--;
	}
}

Vampire::Vampire()
{
	width = 20;
	height = 20;		
	spriteWidth = 40;
	spriteHeight = 40;
	offsetX = 10;
	offsetY = 15;
	if(_sprite == 0) _sprite = load_bitmap("vampire.bmp", 0);
	sprite = _sprite;
	frameStart = frameEnd = 0;
	
	// int state;
	state = 0;
	// int health;
	health = 10;
	// int wakingDistance, wakingSpeed;
	wakingDistance = 140;
	wakingSpeed = 10;
	// int minX, minY, maxX, maxY;
	minX = 60;
	maxX = 570;
	minY = 60;
	maxY = 360;
	// int teleportDistance;
	teleportDistance = 75;
	// int destX, destY;
	destX = x;
	destY = y;
	// bool axis;
	axis = true;
	// int speed, animSpeed;
	speed = 1.5;
	animSpeed = 6;
	// int batCounter, batTime, maxBats;
	batCounter = batTime = 90;
	maxBats = 6;
	// int dieCountdown, dieTime, diePoofDelay;
	dieTime = 240;
	diePoofDelay = 15;
	layer = 2;
	// int blinkingCounter, blinkingTime, blinkingHz;
	blinkingCounter = 0;
	blinkingTime = 60;
	blinkingHz = 6;
	
	if(game.GetQuestState("vampire") == "defeated") alive = false;
}

Entity *Vampire::Create()
{
	return new Vampire;
}