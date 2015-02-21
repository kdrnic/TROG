#include "AKMagazine.h"
#include "Game.h"

AKMagazine::AKMagazine()
{
	name = "AKMagazine";
	icon = (BITMAP *) game.GetData("inv_akMagazine"); // load_bitmap("akmag.bmp", 0);
	equippable = false;
}

Item *AKMagazine::Create()
{
	return new AKMagazine;
}