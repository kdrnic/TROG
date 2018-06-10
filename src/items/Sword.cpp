#include "Sword.h"
#include "Game.h"

Sword::Sword()
{
	icon = (BITMAP *) game.GetData("inv_sword"); // load_bitmap("sword.bmp", 0);
	frames[0] = 4;
	frames[1] = 8;
	damage = 3;
	coolDownTime = 0;
	speed = 5;
	name = "Sword";
	swishes[0] = "snd_swish1";
	swishes[1] = "snd_swish2";
	swishes[2] = "snd_swish3";
}