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

		static constexpr int attackAnimSpeed = 4;
		static constexpr int attackDelay = 90;
		static constexpr float attackOffsetX = 8;
		static constexpr float attackOffsetY = -36;
		static constexpr float attackSpeed = 4;
};

#endif
