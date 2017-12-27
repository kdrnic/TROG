#include <cstdlib>

#include "Game.h"
#include "TriggeredEntity.h"

#include "Button.h"

void Button::SetParameter(std::string p, std::string v)
{
	if(p == "trigger")
	{
		trigger = std::atoi(v.c_str());
		return;
	}
	Entity::SetParameter(p, v);
}

void Button::OnCollision(Entity *e)
{
	if(e == game.player)
	{
		if(game.frame - lastActivationFrame > 1)
		{
			Entity *entities[999];
			int n = game.entitiesManager.FilterEntities("TRIGGERED", entities, 999);
			for(int i = 0; i < n; i++)
			{
				((TriggeredEntity *) entities[i])->OnTrigger(trigger);
			}
		}
		lastActivationFrame = game.frame;
		frameEnd = frameStart = 1;
	}
}

void Button::Update()
{
	if(game.frame - lastActivationFrame > 3) frameEnd = frameStart = 0;
}

Button::Button()
{
	sprite = (BITMAP *) game.GetData("spr_button"); // load_bitmap("button.bmp", 0);
	width = 30;
	spriteWidth = 30;
	height = 30;
	spriteHeight = 30;
	frameStart = frameEnd = 0;
	inverseSpeed = 8;
	offsetX = 0;
	offsetY = 0;
	layer = -1;
	trigger = 0;
	lastActivationFrame = game.frame;
}
