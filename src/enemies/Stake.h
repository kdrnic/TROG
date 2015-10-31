#ifndef STAKE_H
#define STAKE_H

#include "SpriteEntity.h"

class Stake : public SpriteEntity
{
	public:
		static BITMAP *_sprite;
		
		void Update();
		void OnCollision(Entity *e);
		
		Stake(int _x, int _y, int o);
	private:
		int speedX, speedY;
		bool c;
};

#endif