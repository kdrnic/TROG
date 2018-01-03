#include <cmath>
#include <allegro.h>

#include "Utils.h"
#include "Game.h"
#include "Player.h"

#include "Arrow.h"

BITMAP *Arrow::_sprite = 0;

void Arrow::Draw(BITMAP *bmp)
{
	fixed fixAngle;
	RadiansToAllegro(angle, (void *) &fixAngle);
	pivot_sprite(bmp, sprite, int(x) + 1, int(y) + 1, centerX, centerY, fixAngle);
}

void Arrow::OnCollision(Entity *e)
{
	if(e == game.player)
	{
		((Player *) e)->OnHit(1);
		alive = false;
		return;
	}
	if(e->Is("SOLID") && (!e->Is("ENEMY"))) alive = false;
}

void Arrow::Update()
{
	x += speed * std::cos(angle);
	y += speed * std::sin(angle);
	if(x > 630) alive = false;
	if(x < 0) alive = false;
	if(y < 0) alive = false;
	if(y > 420) alive = false;
	if(MapCollision()) alive = false;
}

Arrow::Arrow(float _x, float _y, float a)
{
	if(_sprite == 0) _sprite = (BITMAP *) game.GetData("spr_arrow"); // load_bitmap("arrow.bmp", 0);
	sprite = _sprite;
	angle = a;
	speed = 4.0;
	centerX = 28;
	centerY = 1;
	width = 3;
	height = 3;
	x = _x - (width / 2);
	y = _y - (height / 2);
	damage = 1;
}