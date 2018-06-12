#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <list>
#include <string>

struct BITMAP;

class Map
{
	public:
		struct MapEntity
		{
			unsigned int id;
			int respawnTime;
			std::string name;
			std::vector<std::pair<std::string, std::string> > parameters;
		};
		
		static const int inverseSpeed = 5;
		
		int **blocks;
		int numberOfLayers;
		std::string exits[4];
		std::string name;
		std::list<MapEntity> entities;
		int timeLastVisited;
		
		virtual void Load(std::istream &is) = 0;		
		virtual void Load(std::string fileName) = 0;
		
		virtual void DrawLayer(BITMAP *bmp, BITMAP **tileSet, int layer, int row0, int rows, int x0 = 0, int y0 = 0) = 0;
		
		virtual unsigned int **GetLayers() = 0;
		
		Map() : blocks(0), numberOfLayers(0) {};
};

#endif