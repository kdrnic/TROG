#include "AKMagazine.h"

AKMagazine::AKMagazine()
{
	name = "AKMagazine";
	icon = load_bitmap("akmag.bmp", 0);
	equippable = false;
}

Item *AKMagazine::Create()
{
	return new AKMagazine;
}