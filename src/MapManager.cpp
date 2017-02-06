#include <fstream>
#include <vector>
#include <iostream>
#include <sstream>

#include "MapOwn.h"
#include "Game.h"

void MapManager::LoadTileSet(std::string fileName)
{
	std::fstream tileSetFile;
	tileSetFile.open(fileName.c_str(), std::fstream::in);
	std::vector<std::string> bmpNames;

	while(!tileSetFile.eof())
	{
		std::string bmpName;
		getline(tileSetFile, bmpName);
		if(bmpName == "") continue;
		bmpNames.push_back(bmpName);
	}

	tileSet = new BITMAP *[bmpNames.size()];
	for(int i = 0; i < bmpNames.size(); i++) tileSet[i] = load_bitmap(bmpNames[i].c_str(), 0);
	tileSetFile.close();
	bmpNames.clear();
}

void MapManager::LoadAllMaps(std::string prefix, std::string suffix)
{
	al_ffblk fileInfo;
	if(al_findfirst("maps/*.map", &fileInfo, FA_ALL) == 0)
	{
		while(true)
		{
			std::string fileName = "maps/";
			fileName.append(fileInfo.name);
			
			MapOwn *m = new MapOwn;
			m->Load(fileName.c_str());
			maps[m->name] = (Map *) m;
			
			if(al_findnext(&fileInfo) != 0) break;
		}
	}
}

void MapManager::BeginDrawing(BITMAP *dest, int x, int y)
{
	GameDrawer::BeginDrawing(dest, x, y);
	
	currentMap->DrawLayer(destBitmap, tileSet, 0, 0, 14, topLeftX, topLeftY);
}

void MapManager::DrawRow()
{
	GameDrawer::DrawRow();
	
	currentMap->DrawLayer(destBitmap, tileSet, 1, rowAt, 1, topLeftX, topLeftY);
}

void MapManager::FinishDrawing()
{
	GameDrawer::FinishDrawing();
	
	currentMap->DrawLayer(destBitmap, tileSet, 2, 0, 14, topLeftX, topLeftY);
}

int MapManager::BlockTypeAt(int x, int y)
{
	if(x < 0) x = 0;
	if(x >= 42) x = 41;
	if(y < 0) y = 0;
	if(y >= 28) y = 27;
	return currentMap->blocks[x][y];
}

std::string MapManager::GetExit(int o)
{
	return currentMap->exits[o];
}

void MapManager::SpawnEntities()
{
	for(std::list<Map::MapEntity>::iterator i = currentMap->entities.begin(); i != currentMap->entities.end(); i++)
	{
		if(game.frame - currentMap->timeLastVisited >= i->respawnTime)
		{
			Entity *e = game.entitiesFactory.Create(i->name);
			for(int j = 0; j < i->parameters.size(); j++) e->SetParameter(i->parameters[j].first, i->parameters[j].second);
			game.entitiesManager.Add(e);
		}
	}
	currentMap->timeLastVisited = game.frame;
}

void MapManager::SetMap(std::string n)
{
	currentMap = maps[n];
	currentMapName = n;
}

void MapManager::ResetTimes()
{
	for(std::map<std::string, Map *>::iterator i = maps.begin(); i != maps.end(); i++)
	{
		i->second->timeLastVisited = 0;
	}
}
