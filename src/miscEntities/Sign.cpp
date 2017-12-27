#include "Game.h"
#include "Utils.h"

#include "Sign.h"

BITMAP *Sign::_sprite = 0;

void Sign::SetParameter(std::string p, std::string v)
{
	if(p == "text")
	{
		UnderlinesToSpaces(v);
		text.push_back(v);
		return;
	}
	Entity::SetParameter(p, v);
}

void Sign::Interact()
{
	for(unsigned int i = 0; i < text.size(); i++) game.PushDialogLine(text[i]);
}

Sign::Sign()
{
	if(_sprite == 0) _sprite = (BITMAP *) game.GetData("spr_sign"); // load_bitmap("sign.bmp", 0);
	width = 30;
	height = 30;
	spriteWidth = 30;
	spriteHeight = 30;
	sprite = _sprite;
}
