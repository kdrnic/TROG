#ifndef ZOMBIE_H
#define ZOMBIE_H

#include "HitHurtEnemy.h"

class Zombie : public HitHurtEnemy
{
	public:
		static BITMAP *_sprite;
		
		bool Is(std::string what);
		void Update();
		
		Zombie();
		
		static Entity *Create();
	private:
		int seeDistance;
		int digDistance;
		float runSpeed, walkSpeed;
		int runAnimSpeed, walkAnimSpeed;
		bool outOfHole;
		int visibilityCounter, visibilityTime, runTurnTime;
		int randomWalkCounter, randomWalkTime;
		
		int RandomOrientation(int o);
};

#endif