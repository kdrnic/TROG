#include <cstdlib>

#include "Game.h"
#include "Player.h"
#include "StatueFire.h"
#include <cmath>
#include "Statue.h"

void Statue::SetParameter(std::string what, std::string value)
{
	if((what == "timer")||(what == "phase"))
	{
		attackTimer = atoi(value.c_str());
		return;
	}
	Entity::SetParameter(what, value);
}

bool Statue::Is(std::string what)
{
	if(what == "SOLID") return true;
	return Entity::Is(what);
}

void Statue::Update()
{
	attackTimer--;
	SpriteEntity::Update();

	if(attackTimer == 0)
	{
		frameStart = 1;
		frameEnd = 9;
		counter = 0;
	}

	if((frame == 6) && (nextFrame == 7))
	{
		StatueFire *f = new StatueFire();
		f->x = x + attackOffsetX - f->width * 0.5;
		f->y = y + attackOffsetY - f->height * 0.5;
		float dx = x + attackOffsetX - game.player->x - game.player->width * 0.5;
		float dy = y + attackOffsetY - game.player->y - game.player->width * 0.5;
		float l = -std::sqrt(dx * dx + dy * dy);
		f->speedX = attackSpeed * dx / l;
		f->speedY = attackSpeed * dy / l;
		game.entitiesManager.Add(f);
	}
	if(nextFrame == 9)
	{
		frameStart = 0;
		frameEnd = 0;
		attackTimer = attackDelay;
	}
}

Statue::Statue()
{
	width = 15;
	height = 8;
	spriteWidth = 33;
	spriteHeight = 46;
	offsetX = 9;
	offsetY = 38;
	sprite = (BITMAP *) game.GetData("spr_statue");

	inverseSpeed = attackAnimSpeed;
	attackTimer = attackDelay;
	frameStart = 0;
	frameEnd = 0;
}
