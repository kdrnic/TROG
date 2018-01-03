#include "Game.h"
#include "Player.h"
#include "GenericSword.h"

void GenericSword::OnUse()
{
	if(game.frame - lastFrameUsed >= coolDownTime)
	{
		int randomNumber = rand() % 1000;
		bool success = game.player->Attack(frames[randomNumber >= 500], damage, speed);
		if(success)
		{
			lastFrameUsed = game.frame;
			SAMPLE *s = swishes[rand() % 3];
			if(s != 0) game.player->PlaySample(s);
		}
	}
}

GenericSword::GenericSword()
{
	lastFrameUsed = -999;
	speed = 5;
	coolDownTime = 20;
	swishes[0] = swishes[1] = swishes[2] = 0;
}
