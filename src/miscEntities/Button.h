#ifndef BUTTON_H
#define BUTTON_H

#include "SpriteEntity.h"

class Button : public SpriteEntity
{
	public:
		void SetParameter(std::string p, std::string v);
		void OnCollision(Entity *e);
		void Update();
		
		Button();
	private:
		int lastActivationFrame;
		int trigger;
};

#endif