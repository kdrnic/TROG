#include "Keys.h"
#include "Game.h"
#include "EventEntity.h"
#include "Enemy.h"

#include "Player.h"

#define KEYRIGHT ((rightKey == KeyDown) || (rightKey == KeyPressed))
#define KEYUP ((upKey == KeyDown) || (upKey == KeyPressed))
#define KEYLEFT ((leftKey == KeyDown) || (leftKey == KeyPressed))
#define KEYDOWN ((downKey == KeyDown) || (downKey == KeyPressed))

bool Player::Is(std::string what)
{
	if(what == "PLAYER") return true;
	if(what == "SOLID") return (!falling);
	return false;
}

void Player::Draw(BITMAP *bmp)
{
	if((invulnerabilityCounter == 0) || (((invulnerabilityCounter - (invulnerabilityCounter % (30 / blinkingHz))) / (30 / blinkingHz)) % 2 == 0)) SpriteEntity::Draw(bmp);
}

void Player::Update()
{
	SpriteEntity::Update();

	if(health <= 0)
	{
		if(frameStart != 12)
		{
			frameStart = 12;
			frameEnd = 21;
			counter = 0;
			inverseSpeed = deadAnimSpeed;
		}
		if(frame == 21) dead = true;
		return;
	}

	if(falling) goto Falling;

	if(isAttacking)
	{
		speedX = speedY = 0;
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
		//speedX = speedY = 0;
		int oldO = orientation;

		if(KEYUP)
		{
			speedY += -accel;
			orientation = 0;
		}
		else if(KEYDOWN)
		{
			speedY += accel;
			orientation = 1;
		}
		else
		{
			if(speedY < 0)
			{
				speedY += accel;
				if(speedY > 0) speedY = 0;
			}
			if(speedY > 0)
			{
				speedY -= accel;
				if(speedY < 0) speedY = 0;
			}
		}
		if(KEYLEFT)
		{
			speedX += -accel;
			orientation = 2;
		}
		else if(KEYRIGHT)
		{
			speedX += accel;
			orientation = 3;
		}
		else
		{
			if(speedX < 0)
			{
				speedX += accel;
				if(speedX > 0) speedX = 0;
			}
			if(speedX > 0)
			{
				speedX -= accel;
				if(speedX < 0) speedX = 0;
			}
		}
		if(speedX > maxSpeed) speedX = maxSpeed;
		if(speedX < -maxSpeed) speedX = -maxSpeed;
		if(speedY > maxSpeed) speedY = maxSpeed;
		if(speedY < -maxSpeed) speedY = -maxSpeed;

		if(movedLastFrame)
		{
			switch(oldO)
			{
				case 0:
					if(KEYUP) orientation = 0;
					break;
				case 1:
					if(KEYDOWN) orientation = 1;
					break;
				case 2:
					if(KEYLEFT) orientation = 2;
					break;
				case 3:
					if(KEYRIGHT) orientation = 3;
					break;
			}
		}

		inverseSpeed = walkAnimSpeed;
		frameStart = 0;
		if(KEYUP || KEYLEFT || KEYRIGHT || KEYDOWN)
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
	MoveSolid(speedX, speedY);
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

	if(!CheckFloor(lastFloorX, lastFloorY)) falling = true;

	Falling:
	if(falling)
	{
		if(frameStart != 22)
		{
			switch(orientation)
			{
				case 0:
					y -= 15;
					break;
				case 1:
					y += 15;
					break;
				default:
					break;
			}

			invulnerabilityCounter = 0;

			orientation = 0;
			frameStart = 22;
			frameEnd = 28;
			counter = 0;
			inverseSpeed = deadAnimSpeed;
		}
		else
		{
			if(nextFrame == 28)
			{
				OnHit(fallDamage);

				frameStart = frameEnd = 0;
				inverseSpeed = walkAnimSpeed;
				SpriteEntity::Update();
				falling = false;

				x = lastFloorX;
				y = lastFloorY;

				Entity *entities[10];
				int n = 0;
				n = game.entitiesManager.SearchArea(x, y, width, height, entities, 10);
				for(int i = 0; i < n; i++)
				{
					if(entities[i]->Is("ENEMY"))
					{
						((Enemy *) entities[i])->OnHit(x, y, width, height, fallRespawnHit);
					}
				}
			}
		}
	}
	return;
}

void Player::OnHit(int damage)
{
	if(invulnerabilityCounter > 0) return;
	health -= damage;
	invulnerabilityCounter = invulnerabilityTime;
}

void Player::OnHit(int hx, int hy, int hw, int hh, int damage)
{
	if(health <= 0) return;
	if(!falling)
	{
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
	}
	OnHit(damage);
}

void Player::Heal(int h)
{
	health += h;
	if(health > maxHealth) health = maxHealth;
}

bool Player::Attack(int frame, int damage, int animSpeed)
{
	if(health < 0) return false;
	if(!isAttacking)
	{
		isAttacking = true;
		hasHitEnemy = false;
		frameStart = frame;
		frameEnd = frame + 4;
		attackDamage = damage;
		counter = 0;
		inverseSpeed = animSpeed;
		return true;
	}
	return false;
}

Player::Player()
{
	falling = false;
	fallDamage = 2;
	fallRespawnHit = 2;
	width = 20;
	height = 20;
	persistent = true;
	maxSpeed = 3;
	accel = maxSpeed / 5;
	speedX = speedY = 0;
	health = 0;
	x = 0;
	y = 0;
	inverseSpeed = walkAnimSpeed = 6;
	deadAnimSpeed = 9;
	fallAnimSpeed = 8;
	spriteWidth = spriteHeight = 50;
	offsetX = 15;
	offsetY = 20;
	equippedItems[0] = 0;
	equippedItems[1] = 0;
	sprite = (BITMAP *) game.GetData("spr_gregorius"); // load_bitmap("gregorius.bmp", 0);
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

bool Player::IsEntitySolid(Entity *e)
{
	if(e->Is("ENEMY"))
	{
		if(e->Is("HITHURT")) return false;
	}
	return Entity::IsEntitySolid(e);
}
