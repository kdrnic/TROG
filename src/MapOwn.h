#ifndef MAPOWN_H
#define MAPOWN_H

#include <iostream>
#include <list>
#include <string>

#include <allegro.h>

#include "Map.h"

class MapOwn : public Map
{
	public:
		void Load(std::istream &is);		
		void Load(std::string fileName);
		
		void DrawLayer(BITMAP *bmp, BITMAP **tileSet, int layer, int row0, int rows, int x0 = 0, int y0 = 0);
	private:
		void LoadBlocksLayer(int **&l, std::istream &is);	
		void LoadTilesLayer(int **&l, std::istream &is);		
		void LoadMapEntity(std::string l);
};

#endif