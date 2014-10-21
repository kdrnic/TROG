#include "Game.h"
#include "Player.h"

#include "Skeleton.h"

BITMAP *Skeleton::_sprite = 0;

void Skeleton::Update()
{
	if(frameStart == 4)
	{
		if(attackCountdown == 0)
		{
			frameEnd = 10;
			counter = 0;
		}
		if(attackCountdown <= 0)
		{
			if((!hasHitPlayer) && (frame >= 7))
			{
				Entity *entities[5];
				int n = 0;
				switch(orientation)
				{
					case 0:
						n = game.entitiesManager.SearchArea(x, y - 20, 20, 20, entities, 5);
						break;
					case 1:
						n = game.entitiesManager.SearchArea(x, y + height, 20, 10, entities, 5);
						break;
					case 2:
						n = game.entitiesManager.SearchArea(x - 10, y, 10, 20, entities, 5);
						break;
					case 3:
						n = game.entitiesManager.SearchArea(x + width, y, 10, 20, entities, 5);
						break;
				}
				for(int i = 0; i < n; i++)
				{
					if(entities[i] == game.player)
					{
						hasHitPlayer = true;
						switch(orientation)
						{
							case 0:
								((Player *) entities[i])->OnHit(x, y - 20, 20, 20, attackDamage);
								break;
							case 1:
								((Player *) entities[i])->OnHit(x, y + height, 20, 10, attackDamage);
								break;
							case 2:
								((Player *) entities[i])->OnHit(x - 10, y, 10, 20, attackDamage);
								break;
							case 3:
								((Player *) entities[i])->OnHit(x + width, y, 10, 20, attackDamage);
								break;
						}
					}
				}
			}
		}
		attackCountdown--;
	}
	if(frameStart == 0)
	{
		if(((game.player->x - x) * (game.player->x - x)) + ((game.player->y - y) * (game.player->y - y)) < seeDistance * seeDistance) visibilityCounter = visibilityTime;
		else visibilityCounter--;
		if(visibilityCounter > 0)
		{
			inverseSpeed = walkAnimSpeed;
			if(counter % followTurnTime == 0) Orientate(game.player->x - x, game.player->y - y);
			switch(orientation)
			{
				case 0:
					MoveSolid(0, -walkSpeed);
					break;
				case 1:
					MoveSolid(0, walkSpeed);
					break;
				case 2:
					MoveSolid(-walkSpeed, 0);
					break;
				case 3:
					MoveSolid(walkSpeed, 0);
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
		
		Entity *entities[5];
		int n = 0;
		switch(orientation)
		{
			case 0:
				n = game.entitiesManager.SearchArea(x, y - 5, 20, 5, entities, 5);
				break;
			case 1:
				n = game.entitiesManager.SearchArea(x, y + height, 20, 5, entities, 5);
				break;
			case 2:
				n = game.entitiesManager.SearchArea(x - 10, y, 5, 20, entities, 5);
				break;
			case 3:
				n = game.entitiesManager.SearchArea(x + width, y, 5, 20, entities, 5);
				break;
		}
		for(int i = 0; i < n; i++)
		{
			if(entities[i] == game.player)
			{
				frameStart = 4;
				frameEnd = 4;
				inverseSpeed = attackAnimSpeed;
				counter = 0;
				attackCountdown = attackDelay;
				hasHitPlayer = false;
			}
		}
	}
	if(x <= 0) orientation = 3;
	if(x >= 630) orientation = 2;
	if(y <= 0) orientation = 1;
	if(y >= 420) orientation = 0;
	
	SpriteEntity::Update();
	if(frame == 10)
	{
		frameStart = 0;
		frameEnd = 3;
		inverseSpeed = walkAnimSpeed;
		SpriteEntity::Update();
	}
	Enemy::Update();
}
		
Skeleton::Skeleton()
{
	width = 20;
	height = 20;
	spriteWidth = 50;
	spriteHeight = 62;
	offsetX = 16;
	offsetY = 23;
	if(_sprite == 0) _sprite = load_bitmap("skeleton.bmp", 0);
	sprite = _sprite;
	health = 5;
	walkSpeed = 1.5;
	attackAnimSpeed = 4;
	walkAnimSpeed = 6;
	seeDistance = 100;
	inverseSpeed = 6;
	visibilityCounter = 0;
	visibilityTime = 30;
	randomWalkCounter = 0;
	randomWalkTime = 90;
	frameEnd = 3;
	followTurnTime = 15;
	attackDelay = 2;
	attackDamage = 2;
	MoveToFreeSpot(60, 60, 570, 360);
}

Entity *Skeleton::Create()
{
	return new Skeleton;
}

int Skeleton::RandomOrientation(int o)
{
	return rand() % 4;
}