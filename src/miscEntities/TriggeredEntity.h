#ifndef TRIGGEREDENTITY_H
#define TRIGGEREDENTITY_H

#include "SpriteEntity.h"

class TriggeredEntity : public SpriteEntity
{
	public:
		virtual bool Is(std::string what);
		virtual void OnTrigger(int t);
};

#endif