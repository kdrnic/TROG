#include "Bomb.h"
#include "Game.h"

#include "BombItem.h"

void BombItem::OnActualUse()
{
	game.entitiesManager.Add(new Bomb(game.player->x - 10, game.player->y - 10));
}

BombItem::BombItem()
{
	name = "Bomb";
	iconBg = (BITMAP *) game.GetData("inv_bomb"); // load_bitmap("bombIcon.bmp", 0);
	coolDownTime = 15;
}

Item *BombItem::Create()
{
	return new BombItem;
}