#ifndef GARGOYLEBALL_H
#define GARGOYLEBALL_H

#include "SpriteEntity.h"

#include "Gargoyle.h"

class GargoyleBall : public SpriteEntity
{
	public:
		Gargoyle *father;
		
		void OnCollision(Entity *e);
		void Update();
		
		GargoyleBall(Gargoyle *g, int o);
	private:
		void Die();
};

#endif