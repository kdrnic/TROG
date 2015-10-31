#include "Game.h"
#include "Rat.h"
#include "Poof.h"

#include "Plague.h"

BITMAP *Plague::_sprite = 0;

void Plague::Interact()
{
	if(frameStart == 1)
	{
		game.PushDialogLine("This house is certified to be free of the plague");
		game.PushDialogLine("by Greg's Pest Control Service.");
	}
}

void Plague::Update()
{
	if(frameStart == 0)
	{
		if(game.entitiesManager.Count("RAT") == 0)
		{
			frameStart = frameEnd = 1;
			std::string n = game.mapManager.currentMapName;
			n += ";";
			std::string q = game.GetQuestState("plague");
			int pos = q.find(n);
			game.SetQuestState("plague", q.replace(pos, n.size(), "#"));
			Entity *poof = new Poof(x + width / 2, y + height / 2, 1);
			game.entitiesManager.Add(poof);
			play_sample((SAMPLE *) game.GetData("snd_victory"), 255, 0, 1000, false);
			if(game.GetQuestState("plague").find_first_not_of("#") == std::string::npos)
			{
				game.PushDialogLine("The village has been rid of the plague!");
			}
		}
	}
	SpriteEntity::Update();
}

Plague::Plague()
{
	const int numRats = 6;
	if(_sprite == 0) _sprite = (BITMAP *) game.GetData("spr_plague"); // load_bitmap("plague.bmp", 0);
	width = 30;
	height = 30;
	spriteWidth = 30;
	spriteHeight = 30;
	sprite = _sprite;
	std::string n = game.mapManager.currentMapName;
	n += ";";
	std::string q = game.GetQuestState("plague");
	if(q.find(n) == std::string::npos)
	{
		frameEnd = frameStart = 1;
	}
	else
	{
		frameEnd = frameStart = 0;
		for(int i = 0; i < numRats; i++)
		{
			Entity *rat = new Rat();
			game.entitiesManager.Add(rat);
		}
	}
}