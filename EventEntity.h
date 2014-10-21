#ifndef EVENTENTITY_H
#define EVENTENTITY_H

#include "SpriteEntity.h"

class EventEntity : public SpriteEntity
{
	public:
		virtual bool Is(std::string what);
		
		virtual void Interact();
};

#endif