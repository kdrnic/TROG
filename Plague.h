#ifndef PLAGUE_H
#define PLAGUE_H

#include "EventEntity.h"

class Plague : public EventEntity
{
	public:
		static BITMAP *_sprite;
		
		void Interact();
		void Update();
		
		Plague();
};

#endif