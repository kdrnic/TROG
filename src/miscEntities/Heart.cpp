#include "Game.h"

#include "Heart.h"

BITMAP *Heart::_sprite = 0;

void Heart::OnCollision(Entity *e)
{
	if(e == game.player)
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
		play_sample((SAMPLE *) game.GetData("snd_pickup"), 255, 0, 1000, false);
		alive = false;
	}
}

Heart::Heart()
{
	if(_sprite == 0) _sprite = (BITMAP *) game.GetData("spr_heartPickup"); // load_bitmap("heartPickup.bmp", 0);
	sprite = _sprite;
	width = height = spriteWidth = spriteHeight = 15;
	//orientation = (rand() % 2);
	orientation = 0;
}