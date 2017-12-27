#include "Game.h"
#include "Utils.h"

#include "Chest.h"

#include <cstdlib>

void Chest::SetParameter(std::string p, std::string v)
{
	if(p == "uid")
	{
		uid = std::atoi(v.c_str());
		return;
	}
	if(p == "item")
	{
		item = v;
		return;
	}
	Entity::SetParameter(p, v);
}

void Chest::OnCreate()
{
	if(game.GetQuestState(std::string("chest") + std::string(Itoa(uid))) == "open")
	{
		isOpen = true;
		frameStart = frameEnd = 1;
	}
}

void Chest::Interact()
{
	if(isOpen) return;
	
	Item *newItem = itemsFactory.Create(items[i].substr(0, item.find(":")));
	newItem->SetAmount(std::atoi(items[i].substr(item.find(":") + 1).c_str()));
	inventoryManager.Add(newItem);
	
	isOpen = true;
	frameStart = frameEnd = 1;
	
	game.SetQuestState(std::string("chest") + std::string(Itoa(uid)), "open");
}

Chest::Chest()
{
	sprite = (BITMAP *) game.GetData("spr_chest");
	width = 30;
	height = 30;
	spriteWidth = 30;
	spriteHeight = 30;
	
	frameStart = frameEnd = 0;
	inverseSpeed = 8;
	isOpen = false;
	layer = 0;
}

