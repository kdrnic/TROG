#include <cstdlib>

#include "Game.h"

#include "Poof.h"
#include "BombPickup.h"
#include "Heart.h"

#include "Enemy.h"

bool Enemy::Is(std::string what)
{
	if(what == "ENEMY") return true;
	if(what == "SOLID")
	{
		return true;
	}
	return false;
}

void Enemy::Update()
{
	if(health <= 0)
	{
		Drop();
		alive = false;
	}
}

void Enemy::Die()
{
	Drop();
	alive = false;
	Entity *poof;
	SAMPLE *dyingSound = GetDyingSound();
	if(dyingSound == 0) poof = new Poof(x + width / 2, y + height / 2);
	else
	{
		PlaySample(dyingSound);
		poof = new Poof(x + width / 2, y + height / 2, 0, true);	// Silent poof
	}
	game.entitiesManager.Add(poof);
}

void Enemy::OnHit(int damage)
{
	health -= damage;
	if(health <= 0) Die();
	else
	{
		SAMPLE *hurtSound = GetHurtSound();
		if(hurtSound != 0) PlaySample(hurtSound);
	}
}

void Enemy::OnHit(int hx, int hy, int hw, int hh, int damage)
{
	OnHit(damage);
	if(!alive) return;
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

SAMPLE *Enemy::GetHurtSound()
{
	return 0;
}

SAMPLE *Enemy::GetDyingSound()
{
	return 0;
}

template <class C>
static Entity *InstantiateDrop()
{
	return new C;
}

std::vector<Enemy::CreateDropFunction> Enemy::PossibleDrops()
{
	std::vector<CreateDropFunction> drops;
	drops.push_back(&InstantiateDrop<Heart>);
	if(game.inventoryManager.Find("Bomb") != 0) drops.push_back(&InstantiateDrop<BombPickup>);
	return drops;
}

void Enemy::Drop()
{
	std::vector<CreateDropFunction> drops = PossibleDrops();
	if(rand() % (noDropChance + 1) == 0)
	{
		Entity *drop = drops[rand() % drops.size()]();
		drop->x = x;
		drop->y = y;
		game.entitiesManager.Add(drop);
	}
}

Enemy::Enemy()
{
	hitJump = 29.9;
	noDropChance = 5;
}

bool Enemy::MoveSmart(float dx, float dy)
{
	float oldX = x;
	float oldY = y;
	if(!MoveSolid(dx, dy)) return false;
	if(!CheckFloor())
	{
		x = oldX;
		y = oldY;
		return false;
	}
	return true;
}

bool Enemy::MoveSmart(float speed)
{
	switch(orientation)
	{
		default:
		case 0:
			return MoveSmart(0, -speed);
		case 1:
			return MoveSmart(0, speed);
		case 2:
			return MoveSmart(-speed, 0);
		case 3:
			return MoveSmart(speed, 0);
	}
}