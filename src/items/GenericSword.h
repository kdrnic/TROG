#ifndef GENERICSWORD_H
#define GENERICSWORD_H

#include "Item.h"

class GenericSword : public Item
{
	public:
		virtual void OnUse();

		GenericSword();
	protected:
		int coolDownTime;
		int frames[2];
		int damage;
		int speed;
		SAMPLE *swishes[3];

	private:
		int lastFrameUsed;
};

#endif
