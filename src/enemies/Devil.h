#ifndef DEVIL_H
#define DEVIL_H

#include "Enemy.h"

class Devil : public Enemy
{
	public:
		void Update();
		
		virtual bool Is(std::string what);
		
		Devil();
	private:
		float angle, dAngle;
		int projCounter;
		int angCounter;
		bool hasTalked;
		int talkCounter;
};

#endif