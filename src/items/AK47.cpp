#include "AKBullet.h"
#include "Game.h"

#include "AK47.h"

void AK47::OnUse()
{
	if(hasMag == false)
	{
		if(game.inventoryManager.Find("AKMagazine") != 0)
		{
			hasMag = true;
		}
	}
	if(hasMag)
	{
		if(shotsCounter >= 30)
		{
			shotsCounter = 0;
			voiceId = game.player->PlaySample((SAMPLE *) game.GetData("snd_akReload"), 255);
		}
		else
		{
			if((voiceId < 0) || (voice_check(voiceId) != game.GetData("snd_akReload")))
			{
				game.entitiesManager.Add(new AKBullet(game.player->orientation));
				game.player->PlaySample((SAMPLE *) game.GetData("snd_akShot"), 255, 950 + rand() % 100);
				shotsCounter++;
			}
		}
	}
}

AK47::AK47()
{
	hasMag = false;
	name = "AK47";
	icon = (BITMAP *) game.GetData("inv_ak47"); // load_bitmap("ak47.bmp", 0);
	equippable = true;
	shotsCounter = 0;
	voiceId = -1;
}
