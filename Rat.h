#ifndef RAT_H
#define RAT_H

#include "HitHurtEnemy.h"

class Rat : public HitHurtEnemy
{
	public:
		static BITMAP *_sprite;
		
		bool Is(std::string what);
		void Update();
		
		Rat();
	private:
		bool walking;
		int walkTime;
		int walkCounter;
		int agitation;
		float walkSpeed;
};

#endif