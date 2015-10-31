#ifndef ARCHER_H
#define ARCHER_H

#include "Enemy.h"

class Archer : public Enemy
{
	public:
		static BITMAP *_sprite;
		
		void Update();
		
		Archer();
	private:
		int walkTime;
		int walkCounter;
		float walkSpeed;
		float pathIntegral;
		bool shooting;
		int arrowDistance;
		int walkAnimSpeed;
		int shootAnimSpeed;
		bool hasShot;
		int backupOrientation;
		
		SAMPLE *arrowSounds[3];
};

#endif