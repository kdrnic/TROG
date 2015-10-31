#ifndef HITHURTENEMY_H
#define HITHURTENEMY_H

#include "Enemy.h"

class HitHurtEnemy : public Enemy
{
	public:
		virtual bool Is(std::string w);
		virtual void OnCollision(Entity *e);
		virtual bool IsEntitySolid(Entity *e);
		int hitDamage;
};

#endif