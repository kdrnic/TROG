#ifndef DOOR_H
#define DOOR_H

#include "EventEntity.h"

#include <queue>

class Door : public EventEntity
{
	public:
		static BITMAP *_sprite;
		void SetParameter(std::string p, std::string v);
		bool Is(std::string what);
		void Interact();
		void OnCollision(Entity *e);
		void Update();
		
		Door();
	private:
		bool isOpen;
		std::string map;
		int toX, toY;
};

#endif