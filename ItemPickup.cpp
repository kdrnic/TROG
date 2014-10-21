#include "Game.h"
#include "LimitedAmountItem.h"

#include "ItemPickup.h"

void ItemPickup::OnCollision(Entity *e)
{
	if(e == game.player)
	{
		if(game.inventoryManager.Find(item) != 0)
		{
			((LimitedAmountItem *) game.inventoryManager.Find(item))->AddAmount(amount);
		}
		alive = false;
	}
}