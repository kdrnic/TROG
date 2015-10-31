#ifndef POOF_H
#define POOF_H

#include "SpriteEntity.h"

class Poof : public SpriteEntity
{
	public:
		static BITMAP *_sprite;
		bool soundPlayed;
		
		void Update();
		
		Poof(int _x, int _y, int o = 0, bool silent = false);
};

#endif