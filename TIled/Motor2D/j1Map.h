#ifndef __j1MAP_H__
#define __j1MAP_H__

#include "PugiXml/src/pugixml.hpp"
#include "p2List.h"
#include "p2Point.h"
#include "j1Module.h"

// TODO 2: Create a struct to hold information for a TileSet
// Ignore Terrain Types and Tile Types for now, but we want the image!
struct TileSet
{
	p2SString name;
	uint firstgid;
	uint tilewidth;
	uint tileheight;
	uint spacing;
	uint margin;

	p2SString name_file;
};

// TODO 1: Create a struct needed to hold the information to Map node
enum ORIENTATION
{
	ORTHOGONAL,
	ISOMETRIC,
	STRAGGERED,
	HEXAGONAL
};

enum RENDERORDER
{
	RIGHT_DOWN,
	RIGHT_UP,
	LEFT_DOWN,
	LEFT_UP
};

struct map_info
{
	ORIENTATION orientation;
	RENDERORDER renderorder;
	uint width;
	uint height;
	uint tilewidth;
	uint tileheight;
};

struct Layer
{
	p2SString name;
	 uint width;
	uint height;
	uint* data;
};

// ----------------------------------------------------
class j1Map : public j1Module
{
public:

	j1Map();

	// Destructor
	virtual ~j1Map();

	// Called before render is available
	bool Awake(pugi::xml_node& conf);

	// Called each loop iteration
	void Draw();

	// Called before quitting
	bool CleanUp();

	// Load new map
	bool Load(const char* path);

private:

	bool FillMapInfo(pugi::xml_node&);
	bool FillTileSet();
	bool FillLayer();
	void LogMapData(bool, bool) const;

public:
	
	// TODO 1: Add your struct for map info as public for now
	map_info map;
	p2List<TileSet> tilesets;
	p2List<Layer> layers;

private:

	pugi::xml_document	map_file;
	p2SString			folder;
	p2SString			path_map;
	bool				map_loaded;
	

	SDL_Texture* tileset_texture;

};

#endif // __j1MAP_H__