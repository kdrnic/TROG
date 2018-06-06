#include "Teller.h"
#include "Game.h"
#include "Utils.h"

#include <sstream>

#define QUEST_STRING (game.mapManager.currentMapName + std::string("_teller_") + std::string(Itoa(mapId)))

void Teller::SetParameter(std::string p, std::string v)
{
	if(p == "text")
	{
		if(v.find("\\n") == std::string::npos)
		{
			std::string curr = v;
			std::string line;
			while(true)
			{
				line = curr.substr(0, curr.find("\\n"));
				text.push_back(line);
				if(curr.find("\\n") != std::string::npos) curr = curr.substr(curr.find("\\n") + std::string("\\n").size());
				else break;
			}
			return;
		}
		else
		{
			std::stringstream ss(v);
			std::string line;
			while(!ss.eof())
			{
				std::getline(ss, line);
				text.push_back(line);
			}
		}
	}
}

void Teller::Update()
{
	if(game.GetQuestState(QUEST_STRING) == "done")
	{
		alive = false;
		return;
	}
	for(int i = 0; i < text.size(); i++) game.PushDialogLine(text[i]);
	alive = false;
	game.SetQuestState(QUEST_STRING, "done");
}

Teller::Teller()
{
}