#ifndef AKMAGAZINE_H
#define AKMAGAZINE_H

#include "Item.h"

class AKMagazine : public Item
{
	public:
		AKMagazine();
		
		static Item *Create();
};

#endif