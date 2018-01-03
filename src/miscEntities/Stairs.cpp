#include <cstdlib>

#include "Game.h"
#include "LimitedAmountItem.h"
#include "Player.h"
#include "Stairs.h"

// Opens when the area is cleared of enemies
#define TYPE_AREA_CLEAR 0
// Opens with a key, remains open afterwards
#define TYPE_KEY 1
// Is already open
#define TYPE_OPEN 3
// Is already open, goes up
#define TYPE_OPEN_ASCENDING 2
// Opens when triggered by button
#define TYPE_TRIGGERED 4

void Stairs::SetParameter(std::string p, std::string v)
{
	if(p == "toMap")
	{
		toMap = v;
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
	if(p == "type")
	{
		type = std::atoi(v.c_str());
		return;
	}
	if(p == "id")
	{
		id = v;
		type = TYPE_KEY;
	}
	if(p == "trigger")
	{
		trigger = std::atoi(v.c_str());
		type = TYPE_TRIGGERED;
	}
	SpriteEntity::SetParameter(p, v);
}

void Stairs::OnCollision(Entity *e)
{
	if(type == TYPE_KEY)
	{
		if(frameEnd == 0)
		{
			LimitedAmountItem *keys = (LimitedAmountItem *) game.inventoryManager.Find("Key");
			if(keys != 0)
			{
				if(keys->amount > 0)
				{
					keys->AddAmount(-1);

					frameEnd = 4;
					counter = 0;

					std::string q = game.GetQuestState("stairs");
					q.append(id);
					q.append(";");
					game.SetQuestState("stairs", q);

					PlaySample((SAMPLE *) game.GetData("snd_scrape"), 128);
				}
			}
		}
	}
	if(frameStart == 4)
	{
		if(e == game.player)
		{
			game.SetFadingTransition();
			game.player->x = toX;
			game.player->y = toY;
			game.mapManager.SetMap(toMap);
			game.gameState = GameStateEnteringMap;
		}
	}
}

void Stairs::OnTrigger(int t)
{
	if(t != trigger) return;
	if(type == TYPE_TRIGGERED)
	{
		if((frameEnd == 0) && (game.entitiesManager.Count("ENEMY") == 0))
		{
			frameEnd = 4;
			counter = 0;
			PlaySample((SAMPLE *) game.GetData("snd_scrape"), 128);
		}
	}
}

void Stairs::Update()
{
	if(type == TYPE_AREA_CLEAR)
	{
		if((frameEnd == 0) && (game.entitiesManager.Count("ENEMY") == 0))
		{
			frameEnd = 4;
			counter = 0;
			PlaySample((SAMPLE *) game.GetData("snd_scrape"), 128);
		}
	}
	SpriteEntity::Update();
	if(frame == 4)
	{
		frameStart = 4;
	}
}

void Stairs::OnCreate()
{
	switch(type)
	{
	case TYPE_AREA_CLEAR:
	case TYPE_TRIGGERED:
		orientation = 0;
		frameStart = 0;
		frameEnd = 0;
		layer = -1;
		break;
	case TYPE_KEY:
		orientation = 1;
		frameStart = 0;
		frameEnd = 0;
		layer = -1;
		if(game.GetQuestState("stairs").find(id) != std::string::npos)
		{
			frameStart = frameEnd = 4;
		}
		break;
	case TYPE_OPEN_ASCENDING:
		orientation = 2;
		frameStart = 4;
		frameEnd = 4;
		layer = 0;
		break;
	case TYPE_OPEN:
		orientation = 0;
		frameStart = 4;
		frameEnd = 4;
		layer = -1;
		break;
	}
}

Stairs::Stairs()
{
	sprite = (BITMAP *) game.GetData("spr_stairs");
	width = 30;
	height = 30;
	spriteWidth = 30;
	spriteHeight = 60;
	frameStart = 0;
	frameEnd = 0;
	inverseSpeed = 10;
	offsetX = 0;
	offsetY = 30;
	layer = 0;
	type = 2;
	id = "undefined";
	trigger = 0;
}
