#include "Game.h"
#include "Player.h"

#include "Werewolf.h"

BITMAP *Werewolf::_sprite;

void Werewolf::Update()
{
	int transformationTime = transformationTimeBase + (rand() % transformationTimePlus);
	
	if(isWerewolf)
	{
		if(isTransforming)
		{
			if(nextFrame == 27)
			{
				isTransforming = false;
				isWerewolf = false;
				frameStart = 0;
				frameEnd = 3;
				counter = 0;
				inverseSpeed = humanAnimSpeed;
				transformationCountdown = transformationTime;
				orientation = 1;
			}
		}
		else
		{
			if(isAttacking)
			{
				if((!hasHit) && (frame >= 19))
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
							hasHit = true;
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
				
				if(nextFrame == 21)
				{
					isAttacking = false;
					frameStart = 13;
					frameEnd = 16;
					inverseSpeed = werewolfAnimSpeed;
				}
			}
			else if(isPreparing)
			{
				attackCountdown--;
				if(attackCountdown <= 0)
				{
					isAttacking = true;
					isPreparing = false;
					frameStart = 17;
					frameEnd = 21;
					counter = 0;
					inverseSpeed = attackSpeed;
					hasHit = false;
				}
			}
			else
			{
				if(counter % werewolfTurnTime == 0) Orientate(game.player->x - x, game.player->y - y);
				switch(orientation)
				{
					case 0:
						MoveSolid(0, -werewolfSpeed);
						break;
					case 1:
						MoveSolid(0, werewolfSpeed);
						break;
					case 2:
						MoveSolid(-werewolfSpeed, 0);
						break;
					case 3:
						MoveSolid(werewolfSpeed, 0);
						break;
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
						isPreparing = true;
						frameStart = 17;
						frameEnd = 17;
						attackCountdown = attackDelay;
					}
				}
			}
			
			transformationCountdown--;
			if((transformationCountdown < 0) && (!isAttacking) && (!isPreparing))
			{
				isTransforming = true;
				inverseSpeed = transformationSpeed;
				counter = 0;
				frameStart = 21;
				frameEnd = 27;
			}
		}
	}
	else
	{
		if(isTransforming)
		{
			if(nextFrame == 13)
			{
				isTransforming = false;
				isWerewolf = true;
				frameStart = 13;
				frameEnd = 16;
				counter = 0;
				inverseSpeed = werewolfAnimSpeed;
				transformationCountdown = transformationTime;
				orientation = 1;
			}
		}
		else
		{
			humanWalkCounter--;
			if(humanWalkCounter <= 0)
			{
				int newO = rand() % humanAgitation;
				switch(newO)
				{
					case 0:
					case 1:
					case 2:
					case 3:
						orientation = newO;
						humanWalking = true;
						counter = 0;
						break;
					default:
						humanWalking = false;
						break;
				}
				if(x <= 0) orientation = 3;
				if(x >= 630) orientation = 2;
				if(y <= 0) orientation = 1;
				if(y >= 420) orientation = 0;
				humanWalkCounter = humanWalkTime;
			}
			if(humanWalking)
			{
				frameStart = 0;
				frameEnd = 3;
				switch(orientation)
				{
					case 0:
						MoveSolid(0, -humanSpeed);
						if(GetMinDy() == 0) humanWalkCounter = 0;
						break;
					case 1:
						MoveSolid(0, humanSpeed);
						if(GetMaxDy() == 0) humanWalkCounter = 0;
						break;
					case 2:
						MoveSolid(-humanSpeed, 0);
						if(GetMinDx() == 0) humanWalkCounter = 0;
						break;
					case 3:
						MoveSolid(humanSpeed, 0);
						if(GetMaxDx() == 0) humanWalkCounter = 0;
						break;
				}
			}
			else
			{
				frameStart = 0;
				frameEnd = 0;
			}
			
			transformationCountdown--;
			if(transformationCountdown < 0)
			{
				isTransforming = true;
				PlaySample("snd_howl");
				inverseSpeed = transformationSpeed;
				counter = 0;
				frameStart = 4;
				frameEnd = 13;
			}
		}
	}
	SpriteEntity::Update();
}

void Werewolf::OnHit(int damage)
{
	if(isWerewolf) Enemy::OnHit(damage);
}

void Werewolf::OnHit(int hx, int hy, int hw, int hh, int damage)
{
	if(isWerewolf) Enemy::OnHit(hx, hy, hw, hh, damage);
}

Werewolf::Werewolf()
{
	if(_sprite == 0) _sprite = (BITMAP *) game.GetData("spr_werewolf"); // load_bitmap("werewolf.bmp", 0);
	sprite = _sprite;
	health = 5;
	offsetX = 15;
	offsetY = 20;
	width = 20;
	height = 20;
	spriteWidth = 50;
	spriteHeight = 50;
	MoveToFreeSpot(60, 60, 570, 360);
	
	//bool isTransforming;
	isTransforming = false;
	//bool isWerewolf;
	isWerewolf = rand() % 2;
	if(isWerewolf)
	{
		inverseSpeed = 6;
		frameStart = 13;
		frameEnd = 16;
	}
	else
	{
		inverseSpeed = 8;
		frameStart = 0;
		frameEnd = 3;
	}
	//int transformationSpeed;
	transformationSpeed = 9;
	//int transformationCountdown, transformationTimeBase, transformationTimePlus;	
	transformationTimeBase = 350;
	transformationTimePlus = 100;
	transformationCountdown = transformationTimeBase + (rand() % transformationTimePlus);
	
	//float humanSpeed, humanAnimSpeed;
	humanSpeed = 1.0;
	humanAnimSpeed = 8;
	//bool humanWalking;
	//int humanWalkTime;
	humanWalkTime = 30;
	//int humanWalkCounter;
	humanWalkCounter = 0;
	//int humanAgitation;
	humanAgitation = 8;
	
	//float werewolfSpeed, werewolfAnimSpeed;
	werewolfSpeed = 1.5;
	werewolfAnimSpeed = 6;
	//int werewolfTurnTime;
	werewolfTurnTime = 15;
	
	//bool isAttacking, isPreparing;
	isAttacking = isPreparing = false;
	//int attackCountdown, attackDelay, attackDamage, attackSpeed;
	attackCountdown = 0;
	attackDelay = 2;
	attackDamage = 3;
	attackSpeed = 5;
	//bool hasHit;
	hasHit = false;
}