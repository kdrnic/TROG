#ifndef VAMPIRE_H
#define VAMPIRE_H

#include "SpriteEntity.h"

class Vampire : public SpriteEntity
{
	public:
		static BITMAP *_sprite;
		
		void Draw(BITMAP *bmp);
		bool Is(std::string what);
		bool IsEntitySolid(Entity *e);
		void Update();
		
		void OnHit();
		
		Vampire();
	private:
		int state;
		int health;
		int wakingDistance, wakingSpeed;
		int minX, minY, maxX, maxY;
		int teleportDistance;
		int destX, destY;
		bool axis;
		float speed;
		int animSpeed;
		int batCounter, batTime, maxBats;
		int dieCountdown, dieTime, diePoofDelay;
		int blinkingCounter, blinkingTime, blinkingHz;
};

#endif