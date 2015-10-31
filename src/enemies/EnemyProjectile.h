#ifndef ENEMYPROJECTILE_H
#define ENEMYPROJECTILE_H

#include "Projectile.h"

class EnemyProjectile : public Projectile
{
	public:
		virtual void OnEnemy(Entity *e);
};

#endif