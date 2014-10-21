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
		game.entitiesManager.Add(new AKBullet(game.player->orientation));
	}
}

AK47::AK47()
{
	hasMag = false;
	name = "AK47";
	icon = load_bitmap("ak47.bmp", 0);
	equippable = true;
}

Item *AK47::Create()
{
	return new AK47;
}
