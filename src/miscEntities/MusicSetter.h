#ifndef MUSICSETTER_H
#define MUSICSETTER_H

#include "Entity.h"

class MusicSetter : public Entity
{
	public:
		void SetParameter(std::string p, std::string v);
		void Update();

		MusicSetter();
};

#endif
