#ifndef BAT_H
#define BAT_H

#include "HitHurtEnemy.h"

class Bat : public HitHurtEnemy
{
	public:
		static BITMAP *_sprite;
		
		bool Is(std::string what);
		void Update();
		
		Bat();
		Bat(int _x, int _y);
	private:
		float dx, dy;
};

#endif