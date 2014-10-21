#include "Game.h"

#include "LimitedAmountItem.h"

void LimitedAmountItem::OnUse()
{
	if(amount > 0)
	{
		if(game.frame - lastFrameUsed >= coolDownTime)
		{
			amount--;
			blit(iconBg, icon, 0, 0, 0, 0, 40, 40);
			textprintf_ex(icon, font, 23, 31, 0xFFFFFF, -1, "%02d", amount);
			OnActualUse();			
			lastFrameUsed = game.frame;
		}
	}
}

void LimitedAmountItem::SetAmount(int a)
{
	amount = a;
	blit(iconBg, icon, 0, 0, 0, 0, 40, 40);
	textprintf_ex(icon, font, 23, 31, 0xFFFFFF, -1, "%02d", amount);
}

void LimitedAmountItem::AddAmount(int a)
{
	SetAmount(amount + a);
}

void LimitedAmountItem::OnActualUse()
{
}

LimitedAmountItem::LimitedAmountItem()
{
	icon = create_bitmap(40, 40);
	equippable = true;
	lastFrameUsed = -999;
	coolDownTime = 0;
}