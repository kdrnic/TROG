#include "Game.h"
#include "LimitedAmountItem.h"

#include "ItemPickup.h"

void ItemPickup::OnPickup()
{
	if(game.inventoryManager.Find(item) != 0)
	{
		((LimitedAmountItem *) game.inventoryManager.Find(item))->AddAmount(amount);
	}
}