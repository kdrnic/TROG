#include <sstream>
#include <fstream>
#include <iostream>
#include <cstdlib>

#include "libs\pugixml.hpp"

#include "Utils.h"
#include "Game.h"
#include "MapTiled.h"

using namespace pugi;

void MapTiled::Load(std::istream &is)
{
	static std::map<std::string, BITMAP *> loadedTilesetImages;
	#define ERROR(e) std::cerr << "Error :" << (e) << "\n"; failure = true; return;
	#define WARN(e) std::cerr << "Warning: " << (e) << "\n"; warn = true;
	xml_document doc;
	if(!doc.load(is)) ERROR("XML not parsed")
	
	xml_node n_map = doc.child("map");
	if(!n_map) ERROR("Map node not found")
	
	xml_attribute	a_version = n_map.attribute("version"),
					a_orientation = n_map.attribute("orientation"),
					a_renderorder = n_map.attribute("renderorder"),
					a_width = n_map.attribute("width"),
					a_height = n_map.attribute("height"),
					a_tilewidth = n_map.attribute("tilewidth"),
					a_tileheight = n_map.attribute("tileheight");
	if(!a_version) WARN("Version not found");
	if(!a_orientation) WARN("Orientation not found");
	if(!a_renderorder) WARN("Render order not found");
	
	if(!a_width) ERROR("Width not found");
	if(!a_height) ERROR("Height not found");
	if(!a_tilewidth) ERROR("Tile width not found");
	if(!a_tileheight) ERROR("Tile height not found");
	
	if(std::string(a_version.value()) != "1.0") WARN("Version not 1.0");
	if(std::string(a_orientation.value()) != "orthogonal") WARN("Orientation not orthogonal");
	if(std::string(a_orientation.value()) != "right-down") WARN("Render order not right-down");
	
	if(a_width.as_int() != 21) ERROR("Invalid width");
	if(a_height.as_int() != 14) ERROR("Invalid height");
	if(a_tilewidth.as_int() != 30) ERROR("Invalid tile width");
	if(a_tileheight.as_int() != 30) ERROR("Invalid tile height");
	
	std::vector<xml_node> n_tilesets;
	for(xml_node n = n_map.child("tileset"); n; n = n.next_sibling("tileset")) n_tilesets.push_back(n);
	numberOfTilesets = n_tilesets.size();
	if(numberOfTilesets <= 0) ERROR("No tilesets");
	tilesets = new Tileset[numberOfTilesets];
	
	for(int i = 0; i < n_tilesets.size(); i++)
	{
		xml_node n_tileset = n_tilesets[i];
		Tileset *tileset = &tilesets[i];
		
		xml_attribute a_firstgid, a_name, a_tilewidth, a_tileheight;
		if(!(a_firstgid = n_tileset.attribute("firstgid"))) ERROR("Tileset without firstgid");
		if(!(a_name = n_tileset.attribute("name"))) WARN("Tileset without name");
		if(!(a_tilewidth = n_tileset.attribute("tilewidth"))) WARN("Tileset without tilewidth");
		if(!(a_tileheight = n_tileset.attribute("tileheight"))) WARN("Tileset without tileheight");
		
		if((a_tilewidth.as_int() != 30) || (a_tileheight.as_int() != 30)) ERROR("Invalid tileset tile size");
		
		tileset->firstgid = a_firstgid.as_int();
		tileset->name = a_name.value();
		
		xml_node n_image;
		if(!(n_image = n_tileset.child("image"))) ERROR("Tileset without image");
		
		xml_attribute a_imgSource, a_imgWidth, a_imgHeight;
		if(!(a_imgSource = n_tileset.attribute("source"))) ERROR("Image without source");
		if(!(a_imgWidth = n_tileset.attribute("width"))) WARN("Image without width");
		if(!(a_imgHeight = n_tileset.attribute("height"))) WARN("Image without height");
		
		tileset->imageSource = a_imgSource.value();
		tileset->imageWidth = a_imgWidth.as_int();
		tileset->imageHeight = a_imgHeight.as_int();
		
		std::string imgSourceNoPath = tileset->imageSource.substr(tileset->imageSource.find_last_of("/") + 1);
		std::string imgSourceNoPathNoExtension = imgSourceNoPath.substr(0, imgSourceNoPath.find_last_of("."));
		if(!(tileset->image = (BITMAP *) game.GetData((std::string("tls_") + imgSourceNoPathNoExtension).c_str())))
		{
			WARN("Tileset image not in data file");
			if(loadedTilesetImages.find(imgSourceNoPathNoExtension) == loadedTilesetImages.end()) loadedTilesetImages[imgSourceNoPathNoExtension] = load_bitmap((std::string("tilesets/") + imgSourceNoPath).c_str(), 0);
			if(!loadedTilesetImages[imgSourceNoPathNoExtension]) ERROR("Tileset image not loaded");
			tileset->image = loadedTilesetImages[imgSourceNoPathNoExtension];
		}
	}
	
	#undef ERROR
	#undef WARN
}

void MapTiled::Load(std::string fileName)
{
	failure = false;
	warn = false;
	std::fstream mapFile;
	mapFile.open(fileName.c_str(), std::fstream::in);
	Load(mapFile);
	mapFile.close();
	if(failure || warn)
	{
		std::cerr << "Failure loading " << fileName.c_str() << "\n";
	}
}

void MapTiled::DrawLayer(BITMAP *bmp, BITMAP **tileSet, int layer, int row0, int rows, int x0, int y0)
{
	for(int y = row0; y < row0 + rows; y++)
	{
		for(int x = 0; x < 21; x++)
		{
			//masked_blit(tileSet[tiles[layer][x][y]], bmp, ((game.frame / inverseSpeed) % (tileSet[tiles[2][x][y]]->w / 30)) * 30, 0, x0 + x * 30, y0 + y * 30, 30, 30);
		}
	}
}
