#ifndef BOMB_H
#define BOMB_H

#include "SpriteEntity.h"

class Bomb : public SpriteEntity
{
	public:
		static BITMAP *_sprite;
		
		void Update();
		void OnCollision(Entity *e);
		
		Bomb(int _x, int _y);	
	private:
		void Explode();
};

#endif