#include <sstream>
#include <fstream>
#include <cstdlib>

#include "Utils.h"
#include "Game.h"

#include "Map.h"

int Map::inverseSpeed = 5;

void Map::Load(std::istream &is)
{
	getline(is, name);
	LoadBlocksLayer(blocks, is);
	tiles = new int **[3];
	for(int i = 0; i < 3; i++)
	{
		LoadTilesLayer(tiles[i], is);
	}
	for(int i = 0; i < 4; i++) getline(is, exits[i]);
	while(!is.eof())
	{
		std::string e;
		getline(is, e);
		if(e != "") LoadMapEntity(e);
	}
	timeLastVisited = 0;
}

void Map::Load(std::string fileName)
{
	std::fstream mapFile;
	mapFile.open(fileName.c_str(), std::fstream::in);
	Load(mapFile);
	mapFile.close();
}

void Map::DrawBottomLayers(BITMAP *bmp, BITMAP **tileSet, int x0, int y0)
{
	for(int y = 0; y < 14; y++)
	{
		for(int x = 0; x < 21; x++)
		{
			masked_blit(tileSet[tiles[0][x][y]], bmp, ((game.frame / inverseSpeed) % (tileSet[tiles[0][x][y]]->w / 30)) * 30, 0, x0 + x * 30, y0 + y * 30, 30, 30);
			masked_blit(tileSet[tiles[1][x][y]], bmp, ((game.frame / inverseSpeed) % (tileSet[tiles[1][x][y]]->w / 30)) * 30, 15, x0 + x * 30, y0 + 15 + y * 30, 30, 15);
		}
	}
}

void Map::DrawUpperLayers(BITMAP *bmp, BITMAP **tileSet, int x0, int y0)
{
	for(int y = 0; y < 14; y++)
	{
		for(int x = 0; x < 21; x++)
		{
			masked_blit(tileSet[tiles[1][x][y]], bmp, ((game.frame / inverseSpeed) % (tileSet[tiles[1][x][y]]->w / 30)) * 30, 0, x0 + x * 30, y0 + y * 30, 30, 15);
			masked_blit(tileSet[tiles[2][x][y]], bmp, ((game.frame / inverseSpeed) % (tileSet[tiles[2][x][y]]->w / 30)) * 30, 0, x0 + x * 30, y0 + y * 30, 30, 30);
		}
	}
}

void Map::LoadTilesLayer(int **&l, std::istream &is)
{
	l = new int *[21];
	for(int x = 0; x < 21; x++) l[x] = new int[14];
	for(int y = 0; y < 14; y++)
	{
		std::string line;
		getline(is, line);
		std::vector<std::string> lv = StringToStrings(line);
		for(int x = 0; x < 21; x++)
		{
			l[x][y] = std::atoi(lv[x].c_str());
		}
	}
}

void Map::LoadBlocksLayer(int **&l, std::istream &is)
{
	l = new int *[42];
	int hadouken = 0;
	for(int x = 0; x < 42; x++) l[x] = new int[28];
	for(int y = 0; y < 28; y++)
	{
		std::string line;
		getline(is, line);
		std::vector<std::string> lv = StringToStrings(line);
		for(int x = 0; x < 42; x++)
		{
			hadouken = lv.size();
			l[x][y] = std::atoi(lv[x].c_str());
		}
	}
}

void Map::LoadMapEntity(std::string l)
{
	std::vector<std::string> lv  = StringToStrings(l);
	MapEntity me;
	me.respawnTime = std::atoi(lv[0].c_str());
	me.name = lv[1];
	for(int i = 2; i < lv.size(); i++)
	{
		std::pair<std::string, std::string> parameter;
		parameter.first = lv[i].substr(0, lv[i].find(":"));
		parameter.second = lv[i].substr(lv[i].find(":") + 1);
		me.parameters.push_back(parameter);
	}
	entities.push_back(me);
}