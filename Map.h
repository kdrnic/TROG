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
		
		static int inverseSpeed;
		
		int ***tiles;
		int **blocks;
		std::string exits[4];
		std::string name;
		std::list<MapEntity> entities;
		int timeLastVisited;
		
		void Load(std::istream &is);		
		void Load(std::string fileName);
		
		void DrawBottomLayers(BITMAP *bmp, BITMAP **tileSet, int x0 = 0, int y0 = 0);
		void DrawUpperLayers(BITMAP *bmp, BITMAP **tileSet, int x0 = 0, int y0 = 0);
	private:
		void LoadBlocksLayer(int **&l, std::istream &is);	
		void LoadTilesLayer(int **&l, std::istream &is);		
		void LoadMapEntity(std::string l);
};

#endif