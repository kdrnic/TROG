#include "Enemy.h"
#include "Game.h"

#include "Explosion.h"

BITMAP *Explosion::_sprite = 0;

bool Explosion::Is(std::string what)
{
	if(what == "DETONATOR") return (frame == 3);
	return false;
}

void Explosion::Update()
{
	SpriteEntity::Update();
	if(frame == 5)
	{
		alive = false;
	}
	if(killedAEnemy) canHitEnemies = false;
}

void Explosion::OnCollision(Entity *e)
{
	if(e == game.player) game.player->OnHit(1);
	if(e->Is("ENEMY") && canHitEnemies)
	{
		((Enemy *) e)->OnHit(10);
		killedAEnemy = true;
	}
}

Explosion::Explosion(int _x, int _y)
{
	if(_sprite == 0) _sprite = (BITMAP *) game.GetData("spr_explosion"); // load_bitmap("explosion.bmp", 0);
	x = _x - 59 + 23;
	y = _y - 59 + 23;
	width = 118 - 46;
	height = 118 - 46;
	spriteWidth = 118;
	spriteHeight = 118;
	frameEnd = 7;
	offsetX = 23;
	offsetY = 23;
	inverseSpeed = 3;
	sprite = _sprite;
	canHitEnemies = true;
	killedAEnemy = false;
	layer = 1;
}