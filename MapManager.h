#ifndef MAPMANAGER_H
#define MAPMANAGER_H

#include <map>
#include <string>

#include "Map.h"

class MapManager
{
	public:
		std::string currentMapName;
		
		void LoadTileSet(std::string fileName);		
		void LoadAllMaps(std::string prefix = "map", std::string suffix = ".map");
		
		void DrawUpperLayers(BITMAP *bmp, int x = 0, int y = 0);
		void DrawBottomLayers(BITMAP *bmp, int x = 0, int y = 0);
		
		int BlockTypeAt(int x, int y);		
		std::string GetExit(int o);
		void SpawnEntities();
		void SetMap(std::string n);
		void ResetTimes();
	private:
		BITMAP **tileSet;
		std::map<std::string, Map *> maps;
		Map *currentMap;
};

#endif