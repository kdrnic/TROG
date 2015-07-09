#ifndef BOMBITEM_H
#define BOMBITEM_H

#include "LimitedAmountItem.h"

class BombItem : public LimitedAmountItem
{
	public:
		void OnActualUse();
		
		BombItem();
};

#endif