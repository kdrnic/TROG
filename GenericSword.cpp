#include "Game.h"

#include "GenericSword.h"

void GenericSword::OnUse()
{
	if(game.frame - lastFrameUsed >= coolDownTime)
	{
		int randomNumber = rand() % 1000;
		game.player->Attack(frames[randomNumber >= 500], damage, speed);
		lastFrameUsed = game.frame;
		SAMPLE *s = swishes[rand() % 3];
		if(s != 0) play_sample(s, 255, 0, 1000, false);
	}
}

GenericSword::GenericSword()
{
	lastFrameUsed = -999;
	speed = 5;
	coolDownTime = 20;
	swishes[0] = swishes[1] = swishes[2] = 0;
}