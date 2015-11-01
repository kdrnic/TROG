#ifndef HEART_H
#define HEART_H

#include "Pickup.h"

class Heart : public Pickup
{
	public:
		void OnPickup();
		
		Heart();
};

#endif