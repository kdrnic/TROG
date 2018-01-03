#include "Game.h"
#include "Player.h"
#include "GargoyleBall.h"

#define SPEED 3.75
#define DMG 3

void GargoyleBall::Die()
{
	if(!alive) return;
	alive = false;
	father->BallDied();
}

void GargoyleBall::Update()
{
	const float dx[] = {0, 0, -1, 1};
	const float dy[] = {-1, 1, 0, 0};

	if(x < -50) Die();
	if(x > 700) Die();
	if(y < -50) Die();
	if(y > 480) Die();

	x += dx[orientation] * SPEED;
	y += dy[orientation] * SPEED;

	if(MapCollision()) Die();

	SpriteEntity::Update();
}

void GargoyleBall::OnCollision(Entity *e)
{
	if(e == game.player)
	{
		((Player *) e)->OnHit(3);
		Die();
		return;
	}
	if(e->Is("SOLID") && (!e->Is("ENEMY"))) Die();
}

GargoyleBall::GargoyleBall(Gargoyle *g, int o)
{
	sprite = (BITMAP *) game.GetData("spr_fireball");

	g->GetCenter(x, y);

	father = g;

	width = 8;
	height = 8;
	offsetX = (30 - width) / 2;
	offsetY = (30 - height) / 2;
	spriteWidth = 30;
	spriteHeight = 30;

	x = x - width * 0.5;
	y = y - height * 0.5;

	frameStart = 0;
	frameEnd = 2;
	inverseSpeed = 3;
	orientation = o;
}
