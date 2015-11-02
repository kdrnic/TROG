#ifndef STATUEFIRE_H
#define STATUEFIRE_H

#include "Projectile.h"

class StatueFire : public Projectile
{
	public:
		StatueFire();
		void OnSolid(Entity *e);
};

#endif