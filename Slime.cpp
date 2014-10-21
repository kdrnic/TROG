#include "Game.h"
#include "Goo.h"

#include "Slime.h"

BITMAP *Slime::_sprite = 0;

void Slime::SetParameter(std::string p, std::string v)
{
	Entity::SetParameter(p, v);
}

void Slime::Die()
{
	if(futureGenerations > 0)
	{
		Entity *s = new Slime(futureGenerations - 1);
		s->x = x;
		s->y = y;
		game.entitiesManager.Add(s);
		s = new Slime(futureGenerations - 1);
		s->x = x;
		s->y = y;
		game.entitiesManager.Add(s);
	}
	Enemy::Die();
}

void Slime::Update()
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
				direction = newO;
				walking = true;
				counter = 0;
				break;
			default:
				walking = false;
				break;
		}
		if(x <= 0) direction = 3;
		if(x >= 630) direction = 2;
		if(y <= 0) direction = 1;
		if(y >= 420) direction = 0;
		walkCounter = walkTime;
	}
	if(walking)
	{
		frameStart = 0;
		frameEnd = 3;
		switch(direction)
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
		pathIntegral += walkSpeed;
	}
	else
	{
		frameStart = 0;
		frameEnd = 0;
	}
	if(pathIntegral > 30)
	{
		Entity *g = new Goo(x + width / 2, y + height / 2);
		game.entitiesManager.Add(g);
		pathIntegral -= 30;
	}
	SpriteEntity::Update();
}

Slime::Slime(int fh)
{
	if(_sprite == 0) _sprite = load_bitmap("slime.bmp", 0);
	sprite = _sprite;
	width = 24;
	height = 15;
	offsetX = 3;
	offsetY = 10;
	spriteWidth = 30;
	spriteHeight = 30;
	health = 2;
	hitDamage = 1;
	inverseSpeed = 6;
	frameStart = 0;
	frameEnd = 3;
	walkTime = 60;
	walkSpeed = 1.0;
	walkCounter = 0;
	agitation = 7 + (rand() % 2);
	direction = orientation = 0;
	futureGenerations = fh;
	pathIntegral = 0;
	MoveToFreeSpot(60, 60, 570, 360);
}

Entity *Slime::Create()
{
	return new Slime();
}