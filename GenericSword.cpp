#include "Game.h"

#include "GenericSword.h"

void GenericSword::OnUse()
{
	if(game.frame - lastFrameUsed >= coolDownTime)
	{
		int randomNumber = rand() % 1000;
		game.player->Attack(frames[randomNumber >= 500], damage, speed);
		lastFrameUsed = game.frame;
	}
}

GenericSword::GenericSword()
{
	lastFrameUsed = -999;
	speed = 5;
	coolDownTime = 20;
}