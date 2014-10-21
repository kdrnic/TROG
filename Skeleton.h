#ifndef SKELETON_H
#define SKELETON_H

#include "Enemy.h"

class Skeleton : public Enemy
{
	public:
		static BITMAP *_sprite;
		
		void Update();
		
		Skeleton();
		
		static Entity *Create();
	private:
		int seeDistance;
		float walkSpeed;
		int walkAnimSpeed, attackAnimSpeed;
		int visibilityCounter, visibilityTime, followTurnTime;
		int randomWalkCounter, randomWalkTime;
		int attackCountdown, attackDelay;
		bool hasHitPlayer;
		int attackDamage;
		
		int RandomOrientation(int o);
};

#endif