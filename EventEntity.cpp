#include "EventEntity.h"

bool EventEntity::Is(std::string what)
{
	if(what == "SOLID") return true;
	if(what == "EVENT") return true;
	return false;
}

void EventEntity::Interact()
{
}