#ifndef MAPOWN_H
#define MAPOWN_H

#include <iostream>
#include <list>
#include <string>

struct BITMAP;

#include "Map.h"

class MapOwn : public Map
{
	public:
		int ***tiles;
		
		void Load(std::istream &is);		
		void Load(std::string fileName);
		unsigned int **GetLayers();
		
		void DrawLayer(BITMAP *bmp, BITMAP **tileSet, int layer, int row0, int rows, int x0 = 0, int y0 = 0);
		
		MapOwn();
	private:
		void LoadBlocksLayer(int **&l, std::istream &is);	
		void LoadTilesLayer(int **&l, std::istream &is);		
		void LoadMapEntity(std::string l);
		
		unsigned int entityId;
};

#endif