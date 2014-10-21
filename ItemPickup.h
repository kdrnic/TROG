#ifndef ITEMPICKUP_H
#define ITEMPICKUP_H

#include "SpriteEntity.h"

class ItemPickup : public SpriteEntity
{
	public:
		void OnCollision(Entity *e);
	protected:
		std::string item;
		int amount;
};

#endif