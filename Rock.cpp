#include "Game.h"
#include "Poof.h"

#include "Rock.h"

BITMAP *Rock::_sprite = 0;

bool Rock::Is(std::string what)
{
	if(what == "SOLID") return true;
	return false;
}

void Rock::OnCollision(Entity *e)
{
	if(e->Is("DETONATOR"))
	{
		alive = false;
		Entity *poof = new Poof(x + width / 2, y + height / 2);
		game.entitiesManager.Add(poof);
	}
}

Rock::Rock()
{
	if(_sprite == 0) _sprite = load_bitmap("rock.bmp", 0);
	width = 30;
	height = 30;
	spriteWidth = 30;
	spriteHeight = 30;
	sprite = _sprite;
}

Entity *Rock::Create()
{
	return new Rock;
}