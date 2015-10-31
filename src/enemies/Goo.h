#ifndef GOO_H
#define GOO_H

#include "SpriteEntity.h"

class Goo : public SpriteEntity
{
	public:
		static BITMAP *_sprite;
		
		void Update();
		
		Goo(int _x, int _y, int o = 0);
};

#endif