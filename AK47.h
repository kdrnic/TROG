#ifndef AK47_H
#define AK47_H

#include "Item.h"

class AK47 : public Item
{
	public:
		bool hasMag;
		
		void OnUse();
		
		AK47();
		
		static Item *Create();
};

#endif