#include "Game.h"

#include "Saver.h"

void Saver::Update()
{
    game.Save();
    alive = false;
}

Saver::Saver()
{
    width = 0;
    height = 0;
    x = -9999;
    y = -9999;
}

Entity *Saver::Create()
{
    return new Saver;
}
