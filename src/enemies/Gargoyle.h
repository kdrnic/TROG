#ifndef GARGOYLE_H
#define GARGOYLE_H

#include "SpriteEntity.h"

class Gargoyle : public SpriteEntity
{
	public:
		void BallDied();
		void Update();
		
		void SetParameter(std::string p, std::string v);
		
		Gargoyle();
	private:
		bool ballAlive;
};

#endif