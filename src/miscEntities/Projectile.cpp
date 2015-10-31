#include "Game.h"
#include "Enemy.h"

#include "Projectile.h"

void Projectile::Update()
{
	birthCollision = MapCollision();
	x += speedX;
	y += speedY;
	if(x > 630) alive = false;
	if(x < 0) alive = false;
	if(y < 0) alive = false;
	if(y > 420) alive = false;
	if(MapCollision())
	{
		OnMapCollision(birthCollision);
	}
	else birthCollision = false;
}

void SetSpeed(int _orientation, float speed)
{
	orientation = _orientation;
	switch(orientation)
	{
		case 0:
			speedY = -speed;
			break;
		case 1:
			speedY = speed;
			break;
		case 2:
			speedX = -speed;
			break;
		case 3:
			speedX = speed;
			break;
	}
}

void Projectile::OnPlayer()
{
	game.player->OnHit(x, y, width, height, damage);
	alive = false;
	return;
}

void Projectile::OnEnemy(Entity *e)
{
	((Enemy *) e)->OnHit(x, y, width, height, damage);
	alive = false;
	return;
}

void Projectile::OnSolid(Entity *e)
{
	alive = false;
}

void Projectile::OnMapCollision(bool isCollisionAtBirth)
{
	if(!isCollisionAtBirth) alive = false;
}

void Projectile::OnCollision(Entity *e)
{
	if(e == game.player)
	{
		OnPlayer();
		return;
	}
	if(e->Is("ENEMY"))
	{
		OnEnemy(e);
		return;
	}
	if(e->Is("SOLID"))
	{
		OnSolid(e);
		return;
	}
}

Projectile::Projectile()
{
}