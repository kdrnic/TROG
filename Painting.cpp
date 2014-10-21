#include <cstdlib>

#include "Game.h"
#include "Utils.h"

#include "Painting.h"

BITMAP *Painting::_sprite = 0;

void Painting::SetParameter(std::string p, std::string v)
{
	if(p == "file")
	{
        file = std::atoi(v.c_str());
        std::string canvasFileName = "saves/game";
        canvasFileName += Itoa(file + 1);
        canvasFileName += ".bmp";
        canvas = load_bitmap(canvasFileName.c_str(), 0);
		return;
	}
	Entity::SetParameter(p, v);
}

void Painting::Interact()
{
	game.file = file;
	game.gameState = GameStateFinished;
	game.SetFadingTransition();
}

void Painting::Draw(BITMAP *bmp)
{
    SpriteEntity::Draw(bmp);
    draw_sprite(bmp, canvas, x + 20, y + 20);
}

Painting::Painting()
{
	if(_sprite == 0) _sprite = load_bitmap("frame.bmp", 0);
	width = 200;
	height = 190;
	spriteWidth = 200;
	spriteHeight = 160;
	sprite = _sprite;
	canvas = 0;
}

Painting::~Painting()
{
    if(canvas != 0) destroy_bitmap(canvas);
}

Entity *Painting::Create()
{
	return new Painting;
}
