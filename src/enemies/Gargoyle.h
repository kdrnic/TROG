#ifndef GARGOYLE_H
#define GARGOYLE_H

#include "SpriteEntity.h"

class Gargoyle : public SpriteEntity
{
	public:
		void BallDied();
		void Update();
		
		Gargoyle();
	private:
		bool ballAlive;
};

#endif