#ifndef SIGN_H
#define SIGN_H

#include "EventEntity.h"

#include <queue>

class Sign : public EventEntity
{
	public:
		static BITMAP *_sprite;
		void SetParameter(std::string p, std::string v);
		void Interact();
		
		Sign();
	private:
		std::vector<std::string> text;
};

#endif