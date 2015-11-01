#include "Game.h"

#include "Heart.h"

void Heart::OnPickup()
{
	switch(orientation)
	{
		case 0:
			game.player->Heal(2);
			break;
		case 1:
			game.player->Heal(1);
			break;
		case 2:
			game.player->Heal(0);
			break;
	}
}

Heart::Heart()
{
	sprite = (BITMAP *) game.GetData("spr_heartPickup"); // load_bitmap("heartPickup.bmp", 0);
	width = height = spriteWidth = spriteHeight = 15;
	//orientation = (rand() % 2);
	orientation = 0;
}