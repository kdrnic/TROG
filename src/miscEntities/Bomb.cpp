#include "Explosion.h"
#include "Game.h"

#include "Bomb.h"

BITMAP *Bomb::_sprite = 0;
		
void Bomb::Update()
{
	SpriteEntity::Update();
	if(frame == 16) Explode();
}

void Bomb::OnCollision(Entity *e)
{
	if(e->Is("DETONATOR")) Explode();
}

Bomb::Bomb(int _x, int _y)
{
	if(_sprite == 0) _sprite = (BITMAP *) game.GetData("spr_bomb"); // load_bitmap("bomb.bmp", 0);
	x = _x;
	y = _y;
	width = 30;
	height = 30;
	spriteWidth = 30;
	spriteHeight = 30;
	frameEnd = 17;
	inverseSpeed = 4;
	sprite = _sprite;
}

Bomb::Bomb()
{
	if(_sprite == 0) _sprite = (BITMAP *) game.GetData("spr_bomb"); // load_bitmap("bomb.bmp", 0);
	width = 30;
	height = 30;
	spriteWidth = 30;
	spriteHeight = 30;
	frameEnd = 17;
	inverseSpeed = 4;
	sprite = _sprite;
}

void Bomb::Explode()
{
	alive = false;
	game.entitiesManager.Add(new Explosion(x + 14, y + 17));
	PlaySample("snd_explosion");
}