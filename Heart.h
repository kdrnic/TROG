#ifndef HEART_H
#define HEART_H

#include "SpriteEntity.h"

class Heart : public SpriteEntity
{
	public:
		static BITMAP *_sprite;
		
		void OnCollision(Entity *e);
		
		Heart();
		
		static Entity *Create();
};

#endif