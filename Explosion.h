#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "SpriteEntity.h"

class Explosion : public SpriteEntity
{
	public:
		static BITMAP *_sprite;
		bool killedAEnemy;
		bool canHitEnemies;
		
		bool Is(std::string what);		
		void Update();			
		void OnCollision(Entity *e);
		
		Explosion(int _x, int _y);
};

#endif