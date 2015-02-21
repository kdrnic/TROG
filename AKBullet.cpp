#include "Enemy.h"
#include "Game.h"

#include "AKBullet.h"

BITMAP *AKBullet::_sprite = 0;

void AKBullet::Update()
{
	x += speedX;
	y += speedY;
	if(x > 630) alive = false;
	if(x < 0) alive = false;
	if(y < 0) alive = false;
	if(y > 420) alive = false;
	if(MapCollision()) alive = false;
}

void AKBullet::OnCollision(Entity *e)
{
	if(e->Is("ENEMY"))
	{
		((Enemy *) e)->OnHit(1);
		alive = false;
		return;
	}
	if(e->Is("SOLID") && (e != game.player)) alive = false;
}

AKBullet::AKBullet(int o)
{
	if(_sprite == 0) _sprite = (BITMAP *) game.GetData("spr_bullet"); // load_bitmap("bullet.bmp", 0);
	x = game.player->x;
	y = game.player->y; 
	width = 7;
	height = 5;
	orientation = o;
	speedX = speedY = 0;
	switch(o)
	{
		case 0:
			speedY = -8;
			y -= height;
			x += game.player->width / 2;
			break;
		case 1:
			speedY = 8;
			y += game.player->height;
			x += game.player->width / 2;
			break;
		case 2:
			speedX = -8;
			x -= width;
			y += game.player->height / 2;
			break;
		case 3:
			speedX = 8;
			x += game.player->width;
			y += game.player->height / 2;
			break;
	}
	spriteWidth = 15;
	spriteHeight = 15;
	offsetX = 7;
	offsetY = 7;
	sprite = _sprite;
}