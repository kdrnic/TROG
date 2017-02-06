#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <list>
#include <string>

#include <allegro.h>

class Map
{
	public:
		struct MapEntity
		{
			int respawnTime;
			std::string name;
			std::vector<std::pair<std::string, std::string> > parameters;
		};
		
		static const int inverseSpeed = 5;
		
		int ***tiles;
		int **blocks;
		int numberOfLayers;
		std::string exits[4];
		std::string name;
		std::list<MapEntity> entities;
		int timeLastVisited;
		
		virtual void Load(std::istream &is) = 0;		
		virtual void Load(std::string fileName) = 0;
		
		virtual void DrawLayer(BITMAP *bmp, BITMAP **tileSet, int layer, int row0, int rows, int x0 = 0, int y0 = 0) = 0;
};

#endif