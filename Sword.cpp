#include "Sword.h"

Sword::Sword()
{
	icon = load_bitmap("sword.bmp", 0);
	frames[0] = 4;
	frames[1] = 8;
	damage = 3;
	coolDownTime = 0;
	speed = 5;
	name = "Sword";
}

Item *Sword::Create()
{
	return new Sword;
}