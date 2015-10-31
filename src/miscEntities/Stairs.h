#ifndef STAIRS_H
#define STAIRS_H

#include "TriggeredEntity.h"

#include <queue>

class Stairs : public TriggeredEntity
{
	public:
		void SetParameter(std::string p, std::string v);
		void OnCollision(Entity *e);
		void Update();
		void OnCreate();
		void OnTrigger(int t);
		
		Stairs();
	private:
		int type;
		std::string id;
		std::string toMap;
		int toX, toY;
		int trigger;
};

#endif