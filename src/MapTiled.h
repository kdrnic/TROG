#ifndef MAPTILED_H
#define MAPTILED_H

#include <iostream>
#include <list>
#include <string>

struct BITMAP;

#include "Map.h"

class MapTiled : public Map
{
	public:
		struct Tileset
		{
			int firstgid;
			std::string name;
			std::string imageSource;
			int imageHeight;
			int imageWidth;
			BITMAP *image;
		};
		
		int numberOfTilesets;
		Tileset *tilesets;
		
		void Load(std::istream &is);		
		void Load(std::string fileName);
		void Reload();
		
		void DrawLayer(BITMAP *bmp, BITMAP **tileSet, int layer, int row0, int rows, int x0 = 0, int y0 = 0);
		
		unsigned int **GetLayers();
		
		MapTiled();
	private:
		std::string filename;
		bool failure;
		bool warn;
		
		unsigned int **layers;
		
		bool LoadTileLayer(unsigned int *layer, void *n_data);
		void CallAutoTiler(std::string type, unsigned int *autoLayer);
};

#endif