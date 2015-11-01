#ifndef PICKUP_H
#define PICKUP_H

#include "SpriteEntity.h"

class Pickup : public SpriteEntity
{
	public:
		void OnCollision(Entity *e);
		void OnCreate();
		
		virtual void OnPickup();
		
		void Draw(BITMAP *bmp);
		void Update();
	protected:
		int life;
};

#endif