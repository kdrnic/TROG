#ifndef STAKE_H
#define STAKE_H

#include "Projectile.h"

class Stake : public Projectile
{
	public:
		bool OnAny(Entity *e);
		
		Stake(int _x, int _y, int o);
};

#endif