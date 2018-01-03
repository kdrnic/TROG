#ifndef MAPMANAGER_H
#define MAPMANAGER_H

#include <map>
#include <string>

#include "GameDrawer.h"

class Map;

class MapManager : public GameDrawer
{
	public:
		std::string currentMapName;
		
		void LoadTileSet(std::string fileName);		
		void LoadAllMaps(std::string prefix = "map", std::string suffix = ".map");
		
		void BeginDrawing(BITMAP *dest, int x, int y);
		void DrawRow();
		void FinishDrawing();
		
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