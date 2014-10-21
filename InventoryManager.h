#ifndef INVENTORYMANAGER_H
#define INVENTORYMANAGER_H

#include <set>
#include <string>

#include "Item.h"

class InventoryManager
{
	public:
		BITMAP *inventoryBackground;
		BITMAP *itemSelection;
		
		void Add(Item *i);
		void Remove(Item *i);
		void Clear();
		
		Item *Find(std::string name);
		Item *NextEquippable(Item *i);
		Item *PreviousEquippable(Item *i);
		
		std::string ToString();
		
		void Draw(BITMAP *bmp, int x, int y, Item *selectedItem);
	private:
		std::set<Item *> items;
};

#endif