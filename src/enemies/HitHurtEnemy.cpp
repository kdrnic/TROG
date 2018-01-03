#include "Game.h"
#include "Player.h"
#include "HitHurtEnemy.h"

bool HitHurtEnemy::Is(std::string what)
{
	if(what == "HITHURT") return true;
	return Enemy::Is(what);
}

void HitHurtEnemy::OnCollision(Entity *e)
{
	if(hitDamage != 0)
	{
		if(e == game.player) game.player->OnHit(x, y, width, height, hitDamage);
	}
}

bool HitHurtEnemy::IsEntitySolid(Entity *e)
{
	if(e == game.player) return game.player->dead;
	return Entity::IsEntitySolid(e);
}
