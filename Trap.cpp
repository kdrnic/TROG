#include <cstdlib>

#include "Game.h"
#include "Stake.h"

#include "Trap.h"

BITMAP *Trap::_sprite = 0;

void Trap::SetParameter(std::string p, std::string v)
{
	if(p == "stakeX")
	{
		stakeX = std::atoi(v.c_str());
		return;
	}
	if(p == "stakeY")
	{
		stakeY = std::atoi(v.c_str());
		return;
	}
	if(p == "stakeO")
	{
		stakeO = std::atoi(v.c_str());
		return;
	}
	Entity::SetParameter(p, v);
}

void Trap::OnCollision(Entity *e)
{
	if(e == game.player)
	{
		if(game.frame - lastActivationFrame > 1)
		{
			Entity *stake = new Stake(stakeX, stakeY, stakeO);
			game.entitiesManager.Add(stake);
			play_sample(sounds[rand() % 3], 255, 0, 1000, false);
		}
		lastActivationFrame = game.frame;
		frameEnd = frameStart = 1;
	}
}

void Trap::Update()
{
	if(game.frame - lastActivationFrame > 3) frameEnd = frameStart = 0;
}

Trap::Trap()
{
	sounds[0] = (SAMPLE *) game.GetData("snd_arrow1");
	sounds[1] = (SAMPLE *) game.GetData("snd_arrow2");
	sounds[2] = (SAMPLE *) game.GetData("snd_arrow3");

	if(_sprite == 0) _sprite = (BITMAP *) game.GetData("spr_button"); // load_bitmap("button.bmp", 0);
	sprite = _sprite;
	width = 30;
	spriteWidth = 30;
	height = 30;
	spriteHeight = 30;
	frameStart = frameEnd = 0;
	inverseSpeed = 8;
	offsetX = 0;
	offsetY = 0;
	layer = -1;
	lastActivationFrame = game.frame;
}

Entity *Trap::Create()
{
	return new Trap;
}
