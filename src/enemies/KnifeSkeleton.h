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
		int followTurnTime;
		int randomWalkCounter, randomWalkTime;
		int attackCooldown;

		static constexpr float knifeSpeed = 5.0;
		static constexpr int attackCooldownTime = 60;
		static constexpr float turnDistance = 100;
};

#endif
