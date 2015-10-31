#ifndef TRAP_H
#define TRAP_H

#include "TriggeredEntity.h"

class Trap : public TriggeredEntity
{
	public:
		void SetParameter(std::string p, std::string v);
		void OnTrigger(int t);
		
		Trap();
	private:
		int stakeO;
		int trigger;
		
		SAMPLE *sounds[3];
};

#endif