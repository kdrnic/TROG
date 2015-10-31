#ifndef AKBULLET_H
#define AKBULLET_H

#include "SpriteEntity.h"

class AKBullet : public SpriteEntity
{
	public:
		static BITMAP *_sprite;
		int speedX, speedY;		
		
		void Update();			
		void OnCollision(Entity *e);
		
		AKBullet(int o);
};

#endif