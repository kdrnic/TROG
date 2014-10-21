#include "Keys.h"
#include "Game.h"
#include "EventEntity.h"
#include "Enemy.h"

#include "Player.h"

bool Player::Is(std::string what)
{
	if(what == "PLAYER") return true;
	if(what == "SOLID") return true;
	return false;
}

void Player::Draw(BITMAP *bmp)
{
	if((invulnerabilityCounter == 0) || (((invulnerabilityCounter - (invulnerabilityCounter % (30 / blinkingHz))) / (30 / blinkingHz)) % 2 == 0)) SpriteEntity::Draw(bmp);
}

void Player::Update()
{
	SpriteEntity::Update();
	if(health >= 0)
	{
		if(isAttacking)
		{
			if(frame == frameStart + 4) isAttacking = false;
			else if(!hasHitEnemy)
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
					if(entities[i]->Is("ENEMY"))
					{
						hasHitEnemy = true;
						switch(orientation)
						{
							case 0:
								((Enemy *) entities[i])->OnHit(x, y - 20, 20, 20, attackDamage);
								break;
							case 1:
								((Enemy *) entities[i])->OnHit(x, y + height, 20, 10, attackDamage);
								break;
							case 2:
								((Enemy *) entities[i])->OnHit(x - 10, y, 10, 20, attackDamage);
								break;
							case 3:
								((Enemy *) entities[i])->OnHit(x + width, y, 10, 20, attackDamage);
								break;
						}
					}
				}
			}
		}
		if(!isAttacking)
		{
			float spx, spy;
			spx = spy = 0;
			int oldO = orientation;
			
			if(key[KEY_UP])
			{
				spy = -speed;
				orientation = 0;
			}
			if(key[KEY_DOWN])
			{
				spy = speed;
				orientation = 1;
			}
			if(key[KEY_LEFT])
			{
				spx = -speed;
				orientation = 2;
			}
			if(key[KEY_RIGHT])
			{
				spx = speed;
				orientation = 3;
			}
			MoveSolid(spx, spy);
			
			if(movedLastFrame)
			{
				switch(oldO)
				{
					case 0:
						if(key[KEY_UP]) orientation = 0;
						break;
					case 1:
						if(key[KEY_DOWN]) orientation = 1;
						break;
					case 2:
						if(key[KEY_LEFT]) orientation = 2;
						break;
					case 3:
						if(key[KEY_RIGHT]) orientation = 3;
						break;
				}
			}
			
			inverseSpeed = walkAnimSpeed;
			frameStart = 0;
			if(key[KEY_UP] || key[KEY_LEFT] || key[KEY_RIGHT] || key[KEY_DOWN])
			{
				frameEnd = 3;
				movedLastFrame = true;
			}
			else
			{
				frameEnd = 0;
				movedLastFrame = false;
			}
		}
		if((x + width - 1 < 0) || (x > 630) || (y + height - 1 < 0) || (y > 420))
		{
			game.gameState = GameStateEnteringMap;
			if(y + height - 1 < 0)
			{
				y = 390;
				game.mapManager.SetMap(game.mapManager.GetExit(0));
				game.SetScrollingTransition(0);
			}
			if(y > 420)
			{
				y = 0;
				game.mapManager.SetMap(game.mapManager.GetExit(1));
				game.SetScrollingTransition(1);
			}
			if(x + width - 1 < 0)
			{
				x = 600;
				game.mapManager.SetMap(game.mapManager.GetExit(2));
				game.SetScrollingTransition(2);
			}
			if(x > 630)
			{
				x = 0;
				game.mapManager.SetMap(game.mapManager.GetExit(3));
				game.SetScrollingTransition(3);
			}
		}
		if(xKey == KeyDown)
		{
			if(equippedItems[0] != 0) equippedItems[0]->OnUse();
		}
		if(cKey == KeyDown)
		{
			if(equippedItems[1] != 0) equippedItems[1]->OnUse();
		}
		if(sKey == KeyDown) game.gameState = GameStateInventory;
		if(aKey == KeyDown)
		{
			Entity *entities[5];
			int n = 0;
			switch(orientation)
			{
				case 0:
					n = game.entitiesManager.SearchArea(x, y - 30, width, 30, entities, 5);
					break;
				case 1:
					n = game.entitiesManager.SearchArea(x, y + height, width, 30, entities, 5);
					break;
				case 2:
					n = game.entitiesManager.SearchArea(x - 30, y, 30, height, entities, 5);
					break;
				case 3:
					n = game.entitiesManager.SearchArea(x + width, y, 30, height, entities, 5);
					break;
			}
			for(int i = 0; i < n; i++)
			{
				if(entities[i]->Is("EVENT"))
				{
					((EventEntity *) entities[i])->Interact();
					break;
				}
			}
		}
		if(invulnerabilityCounter > 0) invulnerabilityCounter--;
	}
	else
	{
		if(frameStart != 12)
		{
			frameStart = 12;
			frameEnd = 21;
			counter = 0;
			inverseSpeed = deadAnimSpeed;
		}
		if(frame == 21) dead = true;
	}
}

void Player::OnHit(int damage)
{
	if(invulnerabilityCounter > 0) return;
	health -= damage;
	invulnerabilityCounter = invulnerabilityTime;
}

void Player::OnHit(int hx, int hy, int hw, int hh, int damage)
{
	if(health < 0) return;
	if(x - hx > 0)
	{
		if(y - hy > 0)
		{
			if(hx + hw - x < hy + hh - y) MoveSolid(hitJump, 0);
			else MoveSolid(0, hitJump);
		}
		else
		{
			if(hx + hw - x < y + height - hy) MoveSolid(hitJump, 0);
			else MoveSolid(0, -hitJump);
		}
	}
	else
	{
		if(y - hy > 0)
		{
			if(x + width - hx < hy + hh - y) MoveSolid(-hitJump, 0);
			else MoveSolid(0, hitJump);
		}
		else
		{
			if(x + width - hx < y + height - hy) MoveSolid(-hitJump, 0);
			else MoveSolid(0, -hitJump);
		}
	}
	
	OnHit(damage);
}

void Player::Heal(int h)
{
	health += h;
	if(health > maxHealth) health = maxHealth;
}

void Player::Attack(int frame, int damage, int animSpeed)
{
	if(health < 0) return;
	if(!isAttacking)
	{
		isAttacking = true;
		hasHitEnemy = false;
		frameStart = frame;
		frameEnd = frame + 4;
		attackDamage = damage;
		counter = 0;
		inverseSpeed = animSpeed;
	}
}

Player::Player()
{
	width = 20;
	height = 20;
	persistent = true;
	speed = 3;
	health = 0;
	x = 0;
	y = 0;
	inverseSpeed = walkAnimSpeed = 6;
	deadAnimSpeed = 9;
	spriteWidth = spriteHeight = 50;
	offsetX = 15;
	offsetY = 20;
	equippedItems[0] = 0;
	equippedItems[1] = 0;
	sprite = load_bitmap("gregorius.bmp", 0);
	invulnerabilityCounter = 0;
	blinkingHz = 6;
	invulnerabilityTime = 60;
	gold = 0;
	hitJump = 30;
	isAttacking = false;
	hasHitEnemy = false;
	frameStart = 0;
	frameEnd = 3;
	attackDamage = 0;
	dead = false;
}

Player::~Player()
{
	destroy_bitmap(sprite);
}

bool Player::IsBlockSolid(int b)
{
	return (b != 0);
}

bool Player::IsEntitySolid(Entity *e)
{
	if(e->Is("ENEMY"))
	{
		if(e->Is("HITHURT")) return false;
	}
	return Entity::IsEntitySolid(e);
}