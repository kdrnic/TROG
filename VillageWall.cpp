#include <cstdlib>

#include "Game.h"

#include "VillageWall.h"

void VillageWall::SetParameter(std::string p, std::string v)
{
	Entity::SetParameter(p, v);
	if(x < 0)
	{
		x = -30;
		y = 0;
		width = 30;
		height = 480;
	}
	else if(y < 0)
	{
		y = -30;
		x = 0;
		width = 640;
		height = 30;
	}
	else if(x >= 640)
	{
		x = 640;
		y = 0;
		width = 30;
		height = 480;
	}
	else if(y >= 480)
	{
		y = 480;
		x = 0;
		width = 640;
		height = 30;
	}
}

void VillageWall::OnCollision(Entity *e)
{
	if(coolDown > 0) coolDown --;
	if(e == game.player)
	{
		if(game.GetQuestState("plague").find_first_not_of("#") != std::string::npos)
		{
			if(e->x < 0) e->x = 0;
			if(e->x + e->width - 1 >= 640) e->x = 640 - e->width;
			if(e->y < 0) e->y = 0;
			if(e->y + e->height - 1 >= 480) e->y = 480 - e->height;
			if(coolDown <= 0)
			{
				game.PushDialogLine("You can't leave the village.");
				game.PushDialogLine("It's quarantined due to the plague.");
				coolDown = 45;
			}
		}
	}
}

VillageWall::VillageWall()
{
	coolDown = 0;
}

Entity *VillageWall::Create()
{
	return new VillageWall;
}
