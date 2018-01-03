#include <fstream>
#include <vector>
#include <iostream>
#include <sstream>
#include <allegro.h>

#include "Entity.h"
#include "MapOwn.h"
#include "MapTiled.h"
#include "Game.h"
#include "Utils.h"

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

	al_ffblk fileInfo2;
	if(al_findfirst("maps/*.tmx", &fileInfo2, FA_ALL) == 0)
	{
		while(true)
		{
			std::string fileName = "maps/";
			fileName.append(fileInfo2.name);

			MapTiled *m = new MapTiled;
			m->Load(fileName.c_str());
			maps[m->name] = (Map *) m;

			if(al_findnext(&fileInfo2) != 0) break;
		}
	}

	std::string mapDatN;
	for(int i = 1; game.HasData((mapDatN = std::string("map_") + Itoa(i)).c_str()); i++)
	{
		DATAFILE *d = game.GetDataRaw(mapDatN.c_str());
		std::stringstream ss;
		ss.str(DatafileToString(d));

		MapTiled *m = new MapTiled;
		m->Load(ss);
		maps[m->name] = (Map *) m;
	}
}

void MapManager::BeginDrawing(BITMAP *dest, int x, int y)
{
	GameDrawer::BeginDrawing(dest, x, y);

	for(int i = 0; i < currentMap->numberOfLayers / 2; i++)
	{
		currentMap->DrawLayer(destBitmap, tileSet, i, 0, 14, topLeftX, topLeftY);
	}
}

void MapManager::DrawRow()
{
	GameDrawer::DrawRow();

	currentMap->DrawLayer(destBitmap, tileSet, currentMap->numberOfLayers / 2, rowAt, 1, topLeftX, topLeftY);
}

void MapManager::FinishDrawing()
{
	GameDrawer::FinishDrawing();

	for(int i = (currentMap->numberOfLayers / 2) + 1; i < currentMap->numberOfLayers; i++)
	{
		currentMap->DrawLayer(destBitmap, tileSet, i, 0, 14, topLeftX, topLeftY);
	}
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
			for(int j = 0; j < i->parameters.size(); j++)
			{
				e->SetParameter(i->parameters[j].first, i->parameters[j].second);
			}
			e->mapId = i->id;
			game.entitiesManager.Add(e);
		}
	}
	currentMap->timeLastVisited = game.frame;
}

void MapManager::SetMap(std::string n)
{
	if(maps.find(n) == maps.end())
	{
		std::cerr << "Map not found";
		return;
	}
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
