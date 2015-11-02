#ifndef STATUE_H
#define STATUE_H

#include "SpriteEntity.h"

class Statue : public SpriteEntity
{
	public:
		void SetParameter(std::string what, std::string value);
		bool Is(std::string what);
		
		void Update();
		
		Statue();
	private:
		int attackTimer;
		
		static const int attackAnimSpeed = 4;
		static const int attackDelay = 90;
		static const float attackOffsetX = 8;
		static const float attackOffsetY = -36;
		static const float attackSpeed = 4;
};

#endif