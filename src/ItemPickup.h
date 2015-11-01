#ifndef ITEMPICKUP_H
#define ITEMPICKUP_H

#include "Pickup.h"

class ItemPickup : public Pickup
{
	public:
		void OnPickup();
	protected:
		std::string item;
		int amount;
};

#endif