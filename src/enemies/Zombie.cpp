#include "Game.h"

#include "Zombie.h"
#include "Player.h"
#include "ZombieHole.h"

BITMAP *Zombie::_sprite = 0;

bool Zombie::Is(std::string what)
{
	if(what == "SOLID") return (frame != 0);
	return Enemy::Is(what);
}

void Zombie::Update()
{
	if(!outOfHole)
	{
		if(((game.player->x - x) * (game.player->x - x)) + ((game.player->y - y) * (game.player->y - y)) < digDistance * digDistance)
		{
			if(frameEnd != 15)
			{
				counter = 0;
				PlaySample((SAMPLE *) game.GetData("snd_zombieDig"));
			}
			frameEnd = 15;
		}
	}
	if(nextFrame == 13)
	{
		if(!outOfHole)
		{
			Entity *h = new ZombieHole(x, y);
			game.entitiesManager.Add(h);
		}
		outOfHole = true;
		frameStart = 13;
		frameEnd = 16;
	}
	if(outOfHole)
	{
		if(((game.player->x - x) * (game.player->x - x)) + ((game.player->y - y) * (game.player->y - y)) < seeDistance * seeDistance) visibilityCounter = visibilityTime;
		else visibilityCounter--;
		if(visibilityCounter > 0)
		{
			inverseSpeed = runAnimSpeed;
			if(counter % runTurnTime == 0) Orientate(game.player->x - x, game.player->y - y);
			switch(orientation)
			{
				case 0:
					MoveSolid(0, -runSpeed);
					break;
				case 1:
					MoveSolid(0, runSpeed);
					break;
				case 2:
					MoveSolid(-runSpeed, 0);
					break;
				case 3:
					MoveSolid(runSpeed, 0);
					break;
			}
		}
		else
		{
			inverseSpeed = walkAnimSpeed;
			randomWalkCounter--;
			if(randomWalkCounter <= 0)
			{
				orientation = RandomOrientation(orientation);
				randomWalkCounter = randomWalkTime;
			}
			switch(orientation)
			{
				case 0:
					if(!MoveSolid(0, -walkSpeed)) randomWalkCounter = 0;
					break;
				case 1:
					if(!MoveSolid(0, walkSpeed)) randomWalkCounter = 0;
					break;
				case 2:
					if(!MoveSolid(-walkSpeed, 0)) randomWalkCounter = 0;
					break;
				case 3:
					if(!MoveSolid(walkSpeed, 0)) randomWalkCounter = 0;
					break;
			}
		}
		if(x <= 0) orientation = 3;
		if(x >= 630) orientation = 2;
		if(y <= 0) orientation = 1;
		if(y >= 420) orientation = 0;
	}
	SpriteEntity::Update();
	Enemy::Update();
}

Zombie::Zombie()
{
	width = 20;
	height = 20;
	spriteWidth = 30;
	spriteHeight = 30;
	offsetX = 5;
	offsetY = 10;
	if(_sprite == 0) _sprite = (BITMAP *) game.GetData("spr_zombie"); // load_bitmap("zombie.bmp", 0);
	sprite = _sprite;
	health = 5;
	hitDamage = 2;
	runSpeed = 1.5;
	walkSpeed = 1;
	runAnimSpeed = 6;
	walkAnimSpeed = 8;
	seeDistance = 105;
	digDistance = 140;
	outOfHole = false;
	inverseSpeed = 5;
	visibilityCounter = 0;
	visibilityTime = 30;
	randomWalkCounter = 0;
	randomWalkTime = 90;
	frameEnd = 0;
	runTurnTime = 15;
	MoveToFreeSpot(60, 60, 570, 360);
}

int Zombie::RandomOrientation(int o)
{
	return rand() % 4;
}
