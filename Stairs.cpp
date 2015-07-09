#include <cstdlib>

#include "Game.h"
#include "LimitedAmountItem.h"

#include "Stairs.h"

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
	}
	Entity::SetParameter(p, v);
}

void Stairs::OnCollision(Entity *e)
{
	if(type == 1)
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
					
					play_sample((SAMPLE *) game.GetData("snd_scrape"), 128, 0, 1000, false);
				}
			}
		}
	}
	if(frameStart == 4)
	{
		if(e == game.player)
		{
			game.player->x = toX;
			game.player->y = toY;
			game.mapManager.SetMap(toMap);
			game.SetFadingTransition();
			game.gameState = GameStateEnteringMap;
		}
	}
}

void Stairs::Update()
{
	if(type == 0)
	{
		if((frameEnd == 0) && (game.entitiesManager.Count("ENEMY") == 0))
		{
			frameEnd = 4;
			counter = 0;
			play_sample((SAMPLE *) game.GetData("snd_scrape"), 128, 0, 1000, false);
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
	if(type == 0)
	{
		orientation = 0;
		frameStart = 0;
		frameEnd = 0;
		layer = -1;
	}
	else if(type == 1)
	{
		orientation = 1;
		frameStart = 0;
		frameEnd = 0;
		layer = -1;
		if(game.GetQuestState("stairs").find(id) != std::string::npos)
		{
			frameStart = frameEnd = 4;
		}
	}
	else if(type == 2)
	{
		orientation = 2;
		frameStart = 4;
		frameEnd = 4;
		layer = 0;
	}
	else if(type == 3)
	{
		orientation = 0;
		frameStart = 4;
		frameEnd = 4;
		layer = -1;
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
}