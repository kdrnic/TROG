#include <allegro.h>

#include <sstream>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <utility>

#include "libs\pugixml.hpp"

#include "Utils.h"
#include "Game.h"
#include "JsEngine.h"
#include "MapTiled.h"

using namespace pugi;

int TilesetCompare(const void *a, const void *b)
{
	const MapTiled::Tileset *ta = (MapTiled::Tileset *) a;
	const MapTiled::Tileset *tb = (MapTiled::Tileset *) b;
	if(ta->firstgid < tb->firstgid) return -1;
	if(ta->firstgid > tb->firstgid) return 1;
	return 0;
}

bool MapTiled::LoadTileLayer(unsigned int *layer, void *n_data_ptr)
{
	xml_node n_data = *((xml_node *) n_data_ptr);
	#define ERROR(e) { std::cerr << int(__LINE__) << "\tERROR:\t\t" << (e) << "\n"; failure = true; return true; }
	#define WARN(e) { std::cerr << int(__LINE__) << "\tWARNING:\t" << (e) << "\n"; warn = true; }
	if(!n_data) ERROR("Layer data not found");
	
	xml_attribute a_encoding = n_data.attribute("encoding"), a_compression = n_data.attribute("compression");
	if(!a_encoding) ERROR("Invalid enconding (none)");
	if(std::string(a_encoding.value()) == "base64")
	{
		if(a_compression) ERROR("Data compression unsupported");
		
		std::string data1 = n_data.child_value();
		std::string data2 = RemoveWhitespace(data1);
		std::string data3 = Base64Decode(data2);
		
		std::memcpy(layer, data3.data(), data3.size());
	}
	else if(std::string(a_encoding.value()) == "csv")
	{
		std::string data1 = n_data.child_value();
		std::string data2 = RemoveWhitespace(data1);
		std::string tile;
		std::stringstream ss;
		ss.str(data2);
		while(!ss.eof())
		{
			getline(ss, tile, ',');
			if(!tile.empty()) *(layer++) = std::atoi(tile.c_str());
		}
	}
	else ERROR("Invalid encoding");
	return false;
	#undef ERROR
	#undef WARN
}

void MapTiled::CallAutoTiler(std::string type, unsigned int *autoLayer)
{
	#define WARN(e) { std::cerr << int(__LINE__) << "\tWARNING:\t script engine error #" << (e) << "\n"; warn = true; }
	
	JsEngine *jse = game.scriptEngine->Call("MapAutotile")->PushString(type)->PushBuffer(autoLayer, 42 * 28);
	for(int i = 0; i < numberOfLayers; i++) jse = jse->PushBuffer(layers[i], 42 * 28);
	JsEngine::JsEngineError err = jse->Pop();
	if(err) WARN(err);
	
	#undef WARN
}

void MapTiled::Load(std::istream &is)
{
	#define ERROR(e) { std::cerr << int(__LINE__) << "\tERROR:\t\t" << e << "\n"; failure = true; return; }
	#define WARN(e) { std::cerr << int(__LINE__) << "\tWARNING:\t" << (e) << "\n"; warn = true; }
	static std::map<std::string, BITMAP *> loadedTilesetImages;
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
	if(std::string(a_renderorder.value()) != "right-down") WARN("Render order not right-down");
	
	if(a_width.as_int() != 42) ERROR("Invalid width");
	if(a_height.as_int() != 28) ERROR("Invalid height");
	if(a_tilewidth.as_int() != 15) ERROR("Invalid tile width");
	if(a_tileheight.as_int() != 15) ERROR("Invalid tile height");
	
	if(n_map.child("properties"))
	{
		xml_node n_properties = n_map.child("properties");
		if(n_properties)
		{
			for(xml_node n_property = n_properties.child("property"); n_property; n_property = n_property.next_sibling("property"))
			{
				std::string s_name(n_property.attribute("name").value());
				std::string s_value(n_property.attribute("value").value());
				if(s_name == "name") name = s_value;
				else if(s_name == "west") exits[2] = s_value;
				else if(s_name == "east") exits[3] = s_value;
				else if(s_name == "north") exits[0] = s_value;
				else if(s_name == "south") exits[1] = s_value;
				else WARN("Unknown map property");
			}
		}
	}
	else ERROR("Map properties not found");
	
	std::vector<xml_node> n_tilesets;
	for(xml_node n = n_map.child("tileset"); n; n = n.next_sibling("tileset")) n_tilesets.push_back(n);
	numberOfTilesets = n_tilesets.size();
	if(numberOfTilesets <= 0) ERROR("No tilesets");
	tilesets = new Tileset[numberOfTilesets];
	
	std::map <int, int> tileBits;
	
	Tileset *tilesetBlocks = 0;
	
	for(int i = 0; i < n_tilesets.size(); i++)
	{
		xml_node n_tileset = n_tilesets[i];
		Tileset *tileset = &tilesets[i];
		
		xml_attribute a_firstgid, a_name, a_tilewidth, a_tileheight;
		if(!(a_firstgid = n_tileset.attribute("firstgid"))) ERROR("Tileset without firstgid");
		if(!(a_name = n_tileset.attribute("name"))) WARN("Tileset without name");
		if(!(a_tilewidth = n_tileset.attribute("tilewidth"))) WARN("Tileset without tilewidth");
		if(!(a_tileheight = n_tileset.attribute("tileheight"))) WARN("Tileset without tileheight");
		
		if((a_tilewidth.as_int() != 15) || (a_tileheight.as_int() != 15)) ERROR("Invalid tileset tile size");
		
		if(std::string(a_name.value()) == "blocks")
		{
			if(tilesetBlocks) ERROR("More than one blocks tileset found");
			tilesetBlocks = tileset;
		}
		
		tileset->firstgid = a_firstgid.as_int();
		tileset->name = a_name.value();
		
		xml_node n_image;
		if(!(n_image = n_tileset.child("image"))) ERROR("Tileset without image");
		
		xml_attribute a_imgSource, a_imgWidth, a_imgHeight;
		if(!(a_imgSource = n_image.attribute("source"))) ERROR("Image without source");
		if(!(a_imgWidth = n_image.attribute("width"))) WARN("Image without width");
		if(!(a_imgHeight = n_image.attribute("height"))) WARN("Image without height");
		
		tileset->imageSource = a_imgSource.value();
		tileset->imageWidth = a_imgWidth.as_int();
		tileset->imageHeight = a_imgHeight.as_int();
		
		if(!tilesetBlocks)
		{
			std::string imgSourceNoPath = get_filename(tileset->imageSource.c_str());
			std::string imgSourceNoExt = imgSourceNoPath.substr(0, imgSourceNoPath.find_last_of("."));
			if(!game.HasData((std::string("tls_") + imgSourceNoExt).c_str()))
			{
				if(loadedTilesetImages.find(imgSourceNoExt) == loadedTilesetImages.end())
				{
					loadedTilesetImages[imgSourceNoExt] = load_bitmap((std::string("tilesets/") + imgSourceNoPath).c_str(), 0);
				}
				if(!loadedTilesetImages[imgSourceNoExt])
				{
					ERROR("Tileset image not found, not loaded " << (std::string("tilesets/") + imgSourceNoPath).c_str());
				}
				WARN("Tileset image not in data file");
				tileset->image = loadedTilesetImages[imgSourceNoExt];
			}
			else
			{
				tileset->image = (BITMAP *) game.GetData((std::string("tls_") + imgSourceNoExt).c_str());
			}
		}
		
		std::vector <xml_node> n_tiles;
		for(xml_node n = n_tileset.child("tile"); n; n = n.next_sibling("tile"))
		{
			n_tiles.push_back(n);
		}
		for(int j = 0; j < n_tiles.size(); j++)
		{
			xml_node n_tile = n_tiles[j];
			int id = n_tile.attribute("id").as_int();
			id += tileset->firstgid;
			xml_node n_properties = n_tile.child("properties");
			if(!n_properties) WARN("Tile defined but no properties");
			for(xml_node n_property = n_properties.child("property"); n_property; n_property = n_property.next_sibling("property"))
			{
				std::string name(n_property.attribute("name").value());
				if(name == "bits")
				{
					int bits;
					if(std::sscanf(n_property.attribute("value").value(), "%i", &bits) != 1) WARN("Failure reading bits");
					tileBits[id] = bits;
				}
				else WARN("Unknown property");
			}
		}
	}
	
	for(int i = 0; i < numberOfTilesets - 1; i++)
	{
		if((&tilesets[i]) == tilesetBlocks)
		{
			std::swap(tilesets[i], tilesets[numberOfTilesets - 1]);
			
			tilesetBlocks = &tilesets[numberOfTilesets - 1];
			numberOfTilesets--;
			break;
		}
	}
	
	std::qsort((void *) tilesets, numberOfTilesets, sizeof(Tileset), TilesetCompare);
	
	std::vector<xml_node> n_layers;
	std::vector<xml_node> n_autotiles;
	xml_node n_blocksLayer;
	for(xml_node n = n_map.child("layer"); n; n = n.next_sibling("layer"))
	{
		if(std::string(n.attribute("name").value()) == "blocks")
		{
			n_blocksLayer = n;
		}
		else if(std::string(n.attribute("name").value()).find("autotile_") == 0)
		{
			n_autotiles.push_back(n);
		}
		else n_layers.push_back(n);
	}
	numberOfLayers = n_layers.size();
	if(numberOfLayers <= 0) ERROR("No layers");
	layers = new unsigned int *[numberOfLayers];
	
	unsigned int *blocksLayer = 0;
	
	for(int i = 0; i < numberOfLayers; i++)
	{
		layers[i] = new unsigned int[42 * 28];
		xml_node n_data = n_layers[i].child("data");
		if(LoadTileLayer(layers[i], (void *) &n_data)) return;
	}
	if(n_blocksLayer)
	{
		blocksLayer = new unsigned int[42 * 28];
		xml_node n_data = n_blocksLayer.child("data");
		if(LoadTileLayer(blocksLayer, (void *) &n_data)) return;
	}
	for(unsigned int i = 0; i < n_autotiles.size(); i++)
	{
		unsigned int *autoLayer = new unsigned int[42 * 28];
		xml_node n_data = n_autotiles[i].child("data");
		if(LoadTileLayer(autoLayer, (void *) &n_data)) return;
		CallAutoTiler(std::string(n_autotiles[i].attribute("name").value()).substr(sizeof("autotile_") - 1), autoLayer);
	}
	
	blocks = new int *[42];
	for(int i = 0; i < 42; i++)
	{
		blocks[i] = new int[28];
		std::memset(blocks[i], 0, sizeof(blocks[0][0]) * 28);
	}
	
	for(int x = 0; x < 42; x++)
	{
		for(int y = 0; y < 28; y++)
		{
			int block = 0;
			
			for(int i = 0; i < numberOfLayers + 1; i++)
			{
				unsigned int *layer;
				if(i < numberOfLayers) layer = layers[i];
				else if(blocksLayer) layer = blocksLayer;
				else break;
				
				int tile = layer[x + y * 42];
				if(tileBits.find(tile) != tileBits.end()) block |= tileBits[tile];
			}
			
			blocks[x][y] = block;
		}
	}
	
	xml_node n_objects = n_map.child("objectgroup");
	if(n_objects)
	{
		for(xml_node n_object = n_objects.child("object"); n_object; n_object = n_object.next_sibling("object"))
		{
			MapEntity entity;
			entity.respawnTime = 0;
			
			xml_attribute a_name = n_object.attribute("name");
			if(!a_name) ERROR("Entity lacks name");
			entity.name = a_name.value();
			if(entity.name == "") ERROR("Entity name empty");
			
			entity.id = n_object.attribute("id").as_int();
			
			std::pair<std::string, std::string> parameter;
			
			parameter.first = "x";
			parameter.second = n_object.attribute("x").value();
			entity.parameters.push_back(parameter);
			
			parameter.first = "y";
			parameter.second = n_object.attribute("y").value();
			entity.parameters.push_back(parameter);
			
			xml_node n_properties = n_object.child("properties");
			if(n_properties)
			{
				for(xml_node n_property = n_properties.child("property"); n_property; n_property = n_property.next_sibling("property"))
				{
					parameter.first = n_property.attribute("name").value();
					parameter.second = n_property.attribute("value").value();
					parameter.second += n_property.child_value();
					entity.parameters.push_back(parameter);
				}
			}
			
			entities.push_back(entity);
		}
	}
	else WARN("No entities objects group found");
	
	delete [] blocksLayer;
	
	#undef ERROR
	#undef WARN
	
	timeLastVisited = 0;
}

void MapTiled::Reload()
{
	if(blocks)
	{
		for(int i = 0; i < 42; i++) delete[] blocks[i];
		delete[] blocks;
		blocks = 0;
	}
	
	if(layers)
	{
		for(int i = 0; i < numberOfLayers; i++) delete[] layers[i];
		delete[] layers;
		layers = 0;
	}
	if(tilesets)
	{
		delete[] tilesets;
		tilesets = 0;
	}
	
	numberOfLayers = 0;
	numberOfTilesets = 0;
	failure = false;
	warn = false;
	
	timeLastVisited = 0;
	exits[0] = exits[1] = exits[2] = exits[3] = "";
	
	entities.clear();
	
	Load(filename);
}

void MapTiled::Load(std::string fileName)
{
	filename = fileName;
	failure = false;
	warn = false;
	std::fstream mapFile;
	mapFile.open(fileName.c_str(), std::fstream::in);
	Load(mapFile);
	mapFile.close();
	if(failure || warn)
	{
		if(failure) std::cerr << "Failure loading " << fileName.c_str() << "\n";
		else std::cerr << "Warnings concerning " << fileName.c_str() << "\n";
	}
}

void MapTiled::DrawLayer(BITMAP *bmp, BITMAP **unused, int layer, int row0, int rows, int x0, int y0)
{
	for(int y = row0 * 2; y < (row0 + rows) * 2; y++)
	{
		for(int x = 0; x < 42; x++)
		{
			int tile = layers[layer][x + y * 42];
			if(!tile) continue;
			int tilesetIndex = 0;
			for(int i = 0; i < numberOfTilesets; i++) if(tilesets[i].firstgid < tile) tilesetIndex = i;
			const Tileset *tileset = &tilesets[tilesetIndex];
			
			const int _tile = tile - tileset->firstgid;
			const int rows = tileset->imageWidth / 15;
			const int cols = tileset->imageHeight / 15;
			const int tileC = _tile % rows;
			const int tileR = (_tile - tileC) / rows;
			
			const int sourceX = tileC * 15;
			const int sourceY = tileR * 15;
			BITMAP *t_img = tileset->image;
			
			masked_blit(t_img, bmp, sourceX, sourceY, x0 + x * 15, y0 + y * 15, 15, 15);
		}
	}
}

MapTiled::MapTiled() : Map(), numberOfTilesets(0), tilesets(0), failure(0), warn(0), layers(0)
{
}