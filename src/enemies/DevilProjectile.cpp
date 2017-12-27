#include "Game.h"

#include "DevilProjectile.h"

void DevilProjectile::Update()
{
	if(x < -50) alive = false;
	if(x > 700) alive = false;
	if(y < -50) alive = false;
	if(y > 700) alive = false;
	
	x += dx;
	y += dy;
}

void DevilProjectile::OnCollision(Entity *e)
{
	if(e == game.player)
	{
		((Player *) e)->OnHit(1);
		alive = false;
		return;
	}
}

DevilProjectile::DevilProjectile(float _x, float _y, float _dx, float _dy)
{
	sprite = (BITMAP *) game.GetData("spr_devilproj");
	
	width = 25;
	height = 25;
	offsetX = (sprite->w - width) / 2;
	offsetY = (sprite->w - height) / 2;
	spriteWidth = sprite->w;
	spriteHeight = sprite->w;
	
	x = _x - width * 0.5;
	y = _y - height * 0.5;
	dx = _dx;
	dy = _dy;
	
	frameStart = frameEnd = 0;
	inverseSpeed = 1;
	orientation = 0;
	
	layer = 1;
	
	hitDamage = 0;
}