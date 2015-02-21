#ifndef STAIRS_H
#define STAIRS_H

#include "SpriteEntity.h"

#include <queue>

class Stairs : public SpriteEntity
{
	public:
		void SetParameter(std::string p, std::string v);
		void OnCollision(Entity *e);
		void Update();
		void OnCreate();
		
		Stairs();
		static Entity *Create();
	private:
		int type;
		std::string id;
		std::string toMap;
		int toX, toY;
};

#endif