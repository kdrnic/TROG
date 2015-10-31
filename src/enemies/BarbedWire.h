#ifndef BARBEDWIRE_H
#define BARBEDWIRE_H

#include "HitHurtEnemy.h"

class BarbedWire : public HitHurtEnemy
{
	public:
		static BITMAP *_sprite;
		
		BarbedWire();
};

#endif