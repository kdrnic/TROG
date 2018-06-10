#include <cstdlib>

#include "Game.h"
#include "Stake.h"

#include "Trap.h"

static const char *sounds[3] = {"snd_arrow1", "snd_arrow2", "snd_arrow3"};

void Trap::SetParameter(std::string p, std::string v)
{
	if(p == "stakeO")
	{
		stakeO = std::atoi(v.c_str());
		return;
	}
	if(p == "trigger")
	{
		trigger = std::atoi(v.c_str());
		return;
	}
	Entity::SetParameter(p, v);
}

void Trap::OnTrigger(int t)
{
	if(t == trigger)
	{
		Entity *stake = new Stake(x, y, stakeO);
		game.entitiesManager.Add(stake);
		PlaySample(sounds[rand() % 3], 255);
	}
}

Trap::Trap()
{
	width = 1;
	height = 1;
}
