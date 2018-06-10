#include "Game.h"
#include "Goo.h"
#include "Player.h"
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

const char *Slime::GetDyingSound()
{
	const char *soundNames[] = {"snd_slime1", "snd_slime2", "snd_slime3"};
	return soundNames[rand() % 3];
}

Slime::Slime(int fh)
{
	if(_sprite == 0) _sprite = (BITMAP *) game.GetData("spr_slime"); // load_bitmap("slime.bmp", 0);
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
	walkCounter = walkTime;
	walking = true;
	agitation = 7 + (rand() % 2);
	direction = rand() % 4;
	switch(game.player->orientation)
	{
		case 0:
			if(direction == 1) direction = 0;
			break;
		case 1:
			if(direction == 0) direction = 1;
			break;
		case 2:
			if(direction == 3) direction = 2;
			break;
		case 3:
			if(direction == 2) direction = 3;
			break;
	}
	orientation = 0;
	futureGenerations = fh;
	pathIntegral = 0;
	MoveToFreeSpot(60, 60, 570, 360);
}
