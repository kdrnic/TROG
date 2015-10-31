#include "TriggeredEntity.h"

bool TriggeredEntity::Is(std::string what)
{
	if(what == "TRIGGERED") return true;
	return Entity::Is(what);
}

void TriggeredEntity::OnTrigger(int t)
{
}