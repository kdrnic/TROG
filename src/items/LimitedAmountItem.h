#ifndef LIMITEDAMOUNTITEM_H
#define LIMITEDAMOUNTITEM_H

#include "Item.h"

class LimitedAmountItem : public Item
{
	public:
		void OnUse();
		virtual void OnActualUse();
		void SetAmount(int a);
		void AddAmount(int a);
		
		LimitedAmountItem();
		
	protected:
		int lastFrameUsed;
		int coolDownTime;
		BITMAP *iconBg;	
};

#endif