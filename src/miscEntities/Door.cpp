#include <cstdlib>

#include "Game.h"
#include "Player.h"
#include "Door.h"

BITMAP *Door::_sprite = 0;

bool Door::Is(std::string what)
{
	if(what == "SOLID") return (!isOpen);
	return EventEntity::Is(what);
}

void Door::SetParameter(std::string p, std::string v)
{
	if(p == "toMap")
	{
		map = v;
		return;
	}
	if(p == "toX")
	{
		toX = std::atoi(v.c_str());
		return;
	}
	if(p == "toY")
	{
		toY = std::atoi(v.c_str());
		return;
	}
	if(p == "skin")
	{
		frameStart = frameEnd = std::atoi(v.c_str()) * 4;
		return;
	}
	SpriteEntity::SetParameter(p, v);
}

void Door::Interact()
{
	if(!isOpen)
	{
		counter = 0;
		frameEnd = frameStart + 3;
		PlaySample("snd_door");
	}
}

void Door::OnCollision(Entity *e)
{
	if(isOpen)
	{
		if(e == game.player)
		{
			game.SetFadingTransition();
			game.player->x = toX;
			game.player->y = toY;
			game.mapManager.SetMap(map);
			game.gameState = GameStateEnteringMap;
		}
	}
}

void Door::Update()
{
	SpriteEntity::Update();
	if(frame == frameStart + 3)
	{
		frameStart = frameEnd;
		isOpen = true;
		height = 1;
	}
}

Door::Door()
{
	if(_sprite == 0) _sprite = (BITMAP *) game.GetData("spr_doors"); // load_bitmap("doors.bmp", 0);
	sprite = _sprite;
	width = 30;
	spriteWidth = 60;
	height = 30;
	spriteHeight = 45;
	frameStart = frameEnd = 0;
	inverseSpeed = 8;
	isOpen = false;
	offsetX = 15;
	offsetY = 15;
	layer = -1;
}
