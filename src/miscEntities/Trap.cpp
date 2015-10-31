#include <cstdlib>

#include "Game.h"
#include "Stake.h"

#include "Trap.h"

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
		play_sample(sounds[rand() % 3], 255, 0, 1000, false);
	}
}

Trap::Trap()
{
	sounds[0] = (SAMPLE *) game.GetData("snd_arrow1");
	sounds[1] = (SAMPLE *) game.GetData("snd_arrow2");
	sounds[2] = (SAMPLE *) game.GetData("snd_arrow3");
	
	width = 1;
	height = 1;
}
