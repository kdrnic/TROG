#include "Game.h"
#include "MusicSetter.h"

void MusicSetter::SetParameter(std::string p, std::string v)
{
	if(p == "midi") game.SetMusic(v);
}

void MusicSetter::Update()
{
	alive = false;
}

MusicSetter::MusicSetter()
{
}