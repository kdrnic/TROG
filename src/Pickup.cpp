#include "Game.h"

#include "Pickup.h"

void Pickup::OnCollision(Entity *e)
{
	if(e == game.player)
	{
		OnPickup();
		alive = false;
		PlaySample((SAMPLE *) game.GetData("snd_pickup"));
	}
}

void Pickup::OnCreate()
{
	life = 60 * 7;
}

void Pickup::OnPickup()
{
}

void Pickup::Draw(BITMAP *bmp)
{
	if((life > 160) || (life % 10 >= 5)) SpriteEntity::Draw(bmp);
}

void Pickup::Update()
{
	life--;
	if(life < 0) alive = false;
}