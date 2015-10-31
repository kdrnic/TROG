#ifndef KNIFESKELETON_H
#define KNIFESKELETON_H

#include "Enemy.h"

class KnifeSkeleton : public Enemy
{
	public:
		void Update();
		
		KnifeSkeleton();
	private:
		int seeDistance;
		float walkSpeed;
		int walkAnimSpeed, attackAnimSpeed;
		int visibilityCounter, visibilityTime, followTurnTime;
		int randomWalkCounter, randomWalkTime;
		int attackCooldown;
		
		static const float knifeSpeed = 5.0;
		static const int attackCooldownTime = 60;
		static const float turnDistance = 100;
};

#endif