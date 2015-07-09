#include <cstdlib>

#include "Game.h"

#include "Portal.h"

void Portal::SetParameter(std::string p, std::string v)
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
	if(p == "width")
	{
		width = std::atoi(v.c_str());
		return;
	}
	if(p == "height")
	{
		height = std::atoi(v.c_str());
		return;
	}
	Entity::SetParameter(p, v);
}

void Portal::OnCollision(Entity *e)
{
	if(e == game.player)
	{
		game.player->x = toX;
		game.player->y = toY;
		game.mapManager.SetMap(map);
		game.SetFadingTransition();
		game.gameState = GameStateEnteringMap;
	}
}

Portal::Portal()
{
	width = 30;
	height = 30;
}