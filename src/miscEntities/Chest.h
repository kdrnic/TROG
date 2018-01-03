#ifndef CHEST_H
#define CHEST_H

#include "EventEntity.h"

class Chest : public EventEntity
{
	public:
		void SetParameter(std::string p, std::string v);
		void Interact();
		
		void OnCreate();
		
		Chest();
	private:
		bool isOpen;
		std::string item;
};

#endif