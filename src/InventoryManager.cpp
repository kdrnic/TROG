#include "Utils.h"
#include <allegro.h>
#include "Item.h"
#include "InventoryManager.h"

void InventoryManager::Add(Item *i)
{
	items.insert(i);
}

void InventoryManager::Remove(Item *i)
{
	items.erase(i);
}

void InventoryManager::Clear()
{
	for(std::set<Item *>::iterator i = items.begin(); i != items.end(); i++) delete (*i);
	items.clear();
}

Item *InventoryManager::Find(std::string name)
{
	for(std::set<Item *>::iterator i = items.begin(); i != items.end(); i++)
	{
		if((*i)->name == name) return *i;
	}
	return 0;
}

Item *InventoryManager::NextEquippable(Item *i)
{
	std::set<Item *>::iterator it;
	if(i != 0)
	{
		it = items.find(i);
		it++;
	}
	else it = items.begin();
	while(it != items.end())
	{
		if((*it)->equippable) return *it;
		it++;
	}
	for(it = items.begin(); it != items.end(); it++)
	{
		if((*it)->equippable) return *it;
	}
	return 0;
}

Item *InventoryManager::PreviousEquippable(Item *i)
{
	std::set<Item *>::iterator it;
	if(i != 0)
	{
		it = items.find(i);
		if(it != items.begin()) it--;
		else
		{
			it = items.end();
			it--;
		}
	}
	else
	{
		it = items.end();
		it--;
	}
	while(true)
	{
		if((*it)->equippable) return *it;
		if(it != items.begin()) it--;
		else break;
	}
	for(std::set<Item *>::reverse_iterator rit = items.rbegin(); rit != items.rend(); rit++)
	{
		if((*rit)->equippable) return *rit;
	}
	return 0;
}

std::string InventoryManager::ToString()
{
	std::string inventoryString = "";
	for(std::set<Item *>::iterator i = items.begin(); i != items.end(); i++)
	{
		inventoryString += (*i)->name;
		inventoryString += ':';
		inventoryString += Itoa((*i)->amount);
		std::set<Item *>::iterator j = i;
		if(j++ != items.end()) inventoryString += ' ';
	}
	return inventoryString;
}

void InventoryManager::Draw(BITMAP *bmp, int x, int y, Item *selectedItem)
{
	draw_sprite(bmp, inventoryBackground, x, y);
	int j = 0;
	for(std::set<Item *>::iterator i = items.begin(); i != items.end(); i++)
	{
		if(selectedItem != 0)
		{
			if(selectedItem == (*i)) draw_sprite(bmp, itemSelection, x + 5 + (j % 4) * (45 + 5), y + 5 + (j / 4) * (45 + 5));
		}
		draw_sprite(bmp, (*i)->icon, x + 5 + 2 + (j % 4) * (43 + 5 + 2), y + 5 + 2 + (j / 4) * (43 + 5 + 2));
		j++;
	}
}
