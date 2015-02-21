#include "Game.h"
#include "Utils.h"

#include "NPC.h"

BITMAP *NPC::_sprite = 0;

void NPC::SetParameter(std::string p, std::string v)
{
	if(p == "skin")
	{
		skin = std::atoi(v.c_str());
		return;
	}
	if(p == "text")
	{
		UnderlinesToSpaces(v);
		text.push_back(v);
		return;
	}
	if(p == "walkTime")
	{
		walkTime = std::atoi(v.c_str());
		return;
	}
	if(p == "speed")
	{
		walkSpeed = std::atof(v.c_str());
		return;
	}
	if(p == "agitation")
	{
		agitation = std::atoi(v.c_str());
		return;
	}
	Entity::SetParameter(p, v);
}

void NPC::Interact()
{
	for(int i = 0; i < text.size(); i++) game.PushDialogLine(text[i]);
	frameStart = skin * 4;
	frameEnd = skin * 4;
	walkCounter = walkTime;
	walking = false;
	switch(game.player->orientation)
	{
		case 0:
			orientation = 1;
			break;
		case 1:
			orientation = 0;
			break;
		case 2:
			orientation = 3;
			break;
		case 3:
			orientation = 2;
			break;
	}
	SpriteEntity::Update();
}

void NPC::Update()
{
	walkCounter--;
	if(walkCounter <= 0)
	{
		int newO = rand() % agitation;
		switch(newO)
		{
			case 0:
			case 1:
			case 2:
			case 3:
				orientation = newO;
				walking = true;
				counter = 0;
				break;
			default:
				walking = false;
				break;
		}
		if(x <= 0) orientation = 3;
		if(x >= 630) orientation = 2;
		if(y <= 0) orientation = 1;
		if(y >= 420) orientation = 0;
		walkCounter = walkTime;
	}
	if(walking)
	{
		frameStart = skin * 4;
		frameEnd = (skin * 4) + 3;
		switch(orientation)
		{
			case 0:
				MoveSolid(0, -walkSpeed);
				if(GetMinDy() == 0) walkCounter = 0;
				break;
			case 1:
				MoveSolid(0, walkSpeed);
				if(GetMaxDy() == 0) walkCounter = 0;
				break;
			case 2:
				MoveSolid(-walkSpeed, 0);
				if(GetMinDx() == 0) walkCounter = 0;
				break;
			case 3:
				MoveSolid(walkSpeed, 0);
				if(GetMaxDx() == 0) walkCounter = 0;
				break;
		}
	}
	else
	{
		frameStart = skin * 4;
		frameEnd = skin * 4;
	}
	SpriteEntity::Update();
}

NPC::NPC()
{
	if(_sprite == 0) _sprite = (BITMAP *) game.GetData("spr_npc"); // load_bitmap("NPCs.bmp", 0);
	width = 16;
	height = 18;
	offsetX = 13;
	offsetY = 18;
	spriteWidth = 40;
	spriteHeight = 40;
	sprite = _sprite;
	walkTime = 30;
	walkSpeed = 1.0;
	walkCounter = 0;
	inverseSpeed = 8;
	skin = 0;
	MoveToFreeSpot();
	agitation = 8;
}

Entity *NPC::Create()
{
	return new NPC;
}