#include <fstream>
#include <vector>
#include <iostream>
#include <sstream>

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
	for(int i = 0; true; i++)
	{
		Map *m = new Map;
		std::string fileName = prefix;
		std::stringstream ss;
		ss << i;
		fileName += ss.str();
		fileName += suffix;
		int value = exists(fileName.c_str());
		if(value == 0)
        {
            break;
        }
		m->Load(fileName);
		maps[m->name] = m;
	}
}

void MapManager::DrawBottomLayers(BITMAP *bmp, int x, int y)
{
	currentMap->DrawBottomLayers(bmp, tileSet, x, y);
}

void MapManager::DrawUpperLayers(BITMAP *bmp, int x, int y)
{
	currentMap->DrawUpperLayers(bmp, tileSet, x, y);
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
			game.entitiesManager.Add(e);
			for(int j = 0; j < i->parameters.size(); j++) e->SetParameter(i->parameters[j].first, i->parameters[j].second);
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
