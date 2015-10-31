#include "Game.h"
#include "Player.h"
#include "Knife.h"

#include "KnifeSkeleton.h"

void KnifeSkeleton::Update()
{
	if(frameStart == 4)
	{
		if((frame == 6) && (nextFrame == 7))
		{
			Knife *k = new Knife();
			k->x = x;
			k->y = y;
			switch(orientation)
			{
				case 0:
				case 1:
					k->x += rand() % int(width - k->width);
					break;
				case 2:
				case 3:
					k->y += rand() % int(height - k->height);
			}
			k->SetSpeed(orientation, knifeSpeed);
			game.entitiesManager.Add((Entity *) k);
		}
		if(nextFrame == 8)
		{
			frameStart = 0;
			frameEnd = 3;
			inverseSpeed = walkAnimSpeed;
		}
	}
	if(frameStart == 0)
	{
		if(WithinDistanceTo(game.player, seeDistance))
		{
			if(counter % followTurnTime == 0) Orientate(x - game.player->x, y - game.player->y);
			switch(orientation)
			{
				case 0:
					MoveSmart(0, -walkSpeed);
					break;
				case 1:
					MoveSmart(0, walkSpeed);
					break;
				case 2:
					MoveSmart(-walkSpeed, 0);
					break;
				case 3:
					MoveSmart(walkSpeed, 0);
					break;
			}
		}
		else
		{
			inverseSpeed = walkAnimSpeed;
			randomWalkCounter--;
			if(randomWalkCounter <= 0)
			{
				RandomOrientation(orientation);
				randomWalkCounter = randomWalkTime;
			}
			if(!MoveSmart(walkSpeed)) randomWalkCounter = 0;
			
			if(true)
			{
				Entity *entities[4][20];
				int nEntities[5];
				nEntities[0] = game.entitiesManager.SearchArea(x, y - turnDistance, width, turnDistance, entities[0], 20);
				nEntities[1] = game.entitiesManager.SearchArea(x, y + height, width, turnDistance, entities[1], 20);
				nEntities[2] = game.entitiesManager.SearchArea(x - turnDistance, y, turnDistance, height, entities[2], 20);
				nEntities[3] = game.entitiesManager.SearchArea(x + width, y, turnDistance, height, entities[3], 20);
				for(int i = 0; i < 4; i++)
				{
					bool playerFound = false;
					for(int j = 0; j < nEntities[i]; j++)
					{
						if(entities[i][j] == game.player)
						{
							playerFound = true;
						}
					}
					if(playerFound)
					{
						orientation = i;
						break;
					}
				}
			}
		}
		
		if(attackCooldown <= 0)
		{
			Entity *entities[20];
			int n = 0;
			switch(orientation)
			{
				case 0:
					n = game.entitiesManager.SearchArea(x, y - 999, width, 999, entities, 20);
					break;
				case 1:
					n = game.entitiesManager.SearchArea(x, y + height, width, 999, entities, 20);
					break;
				case 2:
					n = game.entitiesManager.SearchArea(x - 999, y, 999, height, entities, 20);
					break;
				case 3:
					n = game.entitiesManager.SearchArea(x + width, y, 999, height, entities, 20);
					break;
			}
			for(int i = 0; i < n; i++)
			{
				if(entities[i] == game.player)
				{
					frameStart = 4;
					frameEnd = 8;
					inverseSpeed = attackAnimSpeed;
					counter = 0;
					attackCooldown = attackCooldownTime;
				}
			}
		}
	}
	if(x <= 0) orientation = 3;
	if(x >= 630) orientation = 2;
	if(y <= 0) orientation = 1;
	if(y >= 420) orientation = 0;
	
	if(!CheckFloor()) OnHit(999);
	
	SpriteEntity::Update();
	Enemy::Update();
	
	attackCooldown--;
}
		
KnifeSkeleton::KnifeSkeleton()
{
	width = 20;
	height = 20;
	spriteWidth = 50;
	spriteHeight = 62;
	offsetX = 16;
	offsetY = 23;
	sprite = (BITMAP *) game.GetData("spr_knifeSkeleton");
	health = 5;
	walkSpeed = 1.5;
	attackAnimSpeed = 4;
	walkAnimSpeed = 6;
	seeDistance = 100;
	inverseSpeed = 6;
	randomWalkCounter = 0;
	randomWalkTime = 90;
	frameEnd = 3;
	followTurnTime = 15;
	attackCooldown = 0;
	for(int i = 0; i < 20; i++)
	{
		MoveToFreeSpot(60, 60, 570, 360);
		if(CheckFloor()) return;
	}
	alive = false;
}