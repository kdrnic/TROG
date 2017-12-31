#include "Game.h"
#include "Utils.h"

#include "Chest.h"

#include "LimitedAmountItem.h"

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
	SpriteEntity::SetParameter(p, v);
}

void Chest::OnCreate()
{
	if(game.GetQuestState(std::string("chest") + std::string(Itoa(uid))) == "open")
	{
		isOpen = true;
		orientation = 1;
	}
}

void Chest::Interact()
{
	if(isOpen) return;
	
	if(game.inventoryManager.Find(item.substr(0, item.find(":"))) != 0)
	{
		if(item.substr(item.find(":") + 1) != "0")
		{
			((LimitedAmountItem *) game.inventoryManager.Find(item.substr(0, item.find(":"))))->AddAmount(std::atoi(item.substr(item.find(":") + 1).c_str()));
		}
	}
	else
	{
		Item *newItem = game.itemsFactory.Create(item.substr(0, item.find(":")));
		newItem->SetAmount(std::atoi(item.substr(item.find(":") + 1).c_str()));
		game.inventoryManager.Add(newItem);
	}
	
	PlaySample((SAMPLE *) game.GetData("snd_door"));
	
	isOpen = true;
	orientation = 1;
	
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

