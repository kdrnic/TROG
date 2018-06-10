#ifndef NPC_H
#define NPC_H

#include "EventEntity.h"

#include <vector>
#include <string>

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
		std::string script;
		int skin;
		bool walking;
		int walkTime;
		int walkCounter;
		int agitation;
		float walkSpeed;
};

#endif