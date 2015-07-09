#ifndef TRAP_H
#define TRAP_H

#include "SpriteEntity.h"

class Trap : public SpriteEntity
{
	public:
		static BITMAP *_sprite;
		
		void SetParameter(std::string p, std::string v);
		void OnCollision(Entity *e);
		void Update();
		
		Trap();
	private:
		int stakeX, stakeY, stakeO;
		int lastActivationFrame;
		
		SAMPLE *sounds[3];
};

#endif