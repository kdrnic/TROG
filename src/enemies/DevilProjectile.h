#ifndef DEVILPROJECTILE_H
#define DEVILPROJECTILE_H

#include "SpriteEntity.h"

class DevilProjectile : public SpriteEntity
{
	public:
		int hitDamage;
		
		void OnCollision(Entity *e);
		void Update();
		
		DevilProjectile(float _x, float _y, float _dx, float _dy);
	private:
		float dx, dy;
};

#endif