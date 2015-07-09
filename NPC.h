#ifndef NPC_H
#define NPC_H

#include "EventEntity.h"

#include <vector>

class NPC : public EventEntity
{
	public:
		static BITMAP *_sprite;
		void SetParameter(std::string p, std::string v);
		void Interact();
		void Update();
		
		NPC();
	private:
		std::vector<std::string> text;
		int skin;
		bool walking;
		int walkTime;
		int walkCounter;
		int agitation;
		float walkSpeed;
};

#endif