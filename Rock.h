#ifndef ROCK_H
#define ROCK_H

#include "SpriteEntity.h"

class Rock : public SpriteEntity
{
	public:
		static BITMAP *_sprite;
		
		bool Is(std::string what);
		void OnCollision(Entity *e);
		
		Rock();
		static Entity *Create();
};

#endif