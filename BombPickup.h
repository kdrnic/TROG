#ifndef BOMBPICKUP_H
#define BOMBPICKUP_H

#include "ItemPickup.h"

class BombPickup : public ItemPickup
{
	public:
		static BITMAP *_sprite;
		
		BombPickup();
};

#endif