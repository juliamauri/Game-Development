#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1FileSystem.h"
#include "j1Textures.h"
#include "j1Map.h"
#include <math.h>

j1Map::j1Map() : j1Module(), map_loaded(false)
{
	name.create("map");
}

// Destructor
j1Map::~j1Map()
{}

// Called before render is available
bool j1Map::Awake(pugi::xml_node& config)
{
	LOG("Loading Map Parser");
	bool ret = true;

	folder.create(config.child("folder").child_value());

	return ret;
}

void j1Map::Draw()
{
	if(map_loaded == false)
		return;

	// TODO 6: Iterate all tilesets and draw all their 
	// images in 0,0 (you should have only one tileset for now)
	tileset_texture = App->tex->Load(tile[0].name_file.GetString());
	App->render->Blit(tileset_texture, 0, 0);

}

// Called before quitting
bool j1Map::CleanUp()
{
	LOG("Unloading map");

	App->tex->UnLoad(tileset_texture);

	// TODO 2: Make sure you clean up any memory allocated
	// from tilesets / map

	// Remove all tilesets


	map_file.reset();

	return true;
}

// Load new map
bool j1Map::Load(const char* file_name)
{
	bool ret = true;
	path_map.create(file_name);
	p2SString tmp("%s%s", folder.GetString(), file_name);

	char* buf;
	int size = App->fs->Load(tmp.GetString(), &buf);
	pugi::xml_parse_result result = map_file.load_buffer(buf, size);

	RELEASE(buf);

	if(result == NULL)
	{
		LOG("Could not load map xml file %s. pugi error: %s", file_name, result.description());
		ret = false;
	}

	bool loadmap = true;

	if(ret == true)
	{
		// TODO 3: Create and call a private function to load and fill
		// all your map data
		loadmap = FillMapInfo(map_file.child("map"));
	}

	// TODO 4: Create and call a private function to load a tileset
	// remember to support more any number of tilesets!
	bool loadtiles = FillTileSet();

	// TODO 5: LOG all the data loaded
	// iterate all tilesets and LOG everything
	LogMapData(loadmap,loadtiles);

	map_loaded = ret;

	return ret;
}

bool j1Map::FillMapInfo(pugi::xml_node& map_info)
{
	bool ret = true;

	p2SString orientation = map_info.attribute("orientation").as_string();

	if (orientation == "orthogonal")
		map.orientation = ORIENTATION::ORTHOGONAL;
	else if (orientation == "isometric")
		map.orientation = ORIENTATION::ISOMETRIC;
	else if (orientation == "staggered")
		map.orientation = ORIENTATION::STRAGGERED;
	else if (orientation == "hexagonal")
		map.orientation = ORIENTATION::HEXAGONAL;

	p2SString renderorder = map_info.attribute("renderorder").as_string();

	if (renderorder == "right-down")
		map.renderorder = RENDERORDER::RIGHT_DOWN;
	else if (renderorder == "right-up")
		map.renderorder = RENDERORDER::RIGHT_UP;
	else if (renderorder == "left-down")
		map.renderorder = RENDERORDER::LEFT_DOWN;
	else if (renderorder == "left-up")
		map.renderorder = RENDERORDER::LEFT_UP;

	map.width = map_info.attribute("width").as_uint();
	map.height = map_info.attribute("height").as_uint();
	map.tilewidth = map_info.attribute("tilewidth").as_uint();
	map.tileheight = map_info.attribute("tileheight").as_uint();

	return ret;
}

bool j1Map::FillTileSet()
{
	bool ret = true;

	for (pugi::xml_node tileset = map_file.child("map").child("tileset"); tileset; tileset = tileset.next_sibling("tileset"))
	{
		count_tileset = 0;

		tile[count_tileset].name = tileset.attribute("name").as_string();

		tile[count_tileset].firstgid = tileset.attribute("firstgid").as_uint();

		tile[count_tileset].tileheight = tileset.attribute("tileheight").as_uint();

		tile[count_tileset].tilewidth = tileset.attribute("tilewidth").as_uint();

		tile[count_tileset].spacing = tileset.attribute("spacing").as_uint();

		tile[count_tileset].margin = tileset.attribute("margin").as_uint();

		tile[count_tileset].name_file = folder.GetString();
		tile[count_tileset].name_file += map_file.child("map").child("tileset").child("image").attribute("source").as_string();

		count_tileset++;
	}

	

	return ret;

	//atoi, convert char to int
}

void j1Map::LogMapData(bool loadmap, bool loadtiles) const
{
	if (loadmap && loadmap)
	{
		LOG("Successfully parsed map XML file: %s", path_map.GetString());
	}
	else
		LOG("Error loading map XML file: %s", path_map.GetString());

	LOG("width: %d" , map.width);
	LOG("height: %d", map.height);
	LOG("tilewidth: %d", map.tilewidth);
	LOG("tileheight: %d", map.tileheight);

	LOG("TileSet----");
	for (uint i = 0; i < count_tileset; i++)
	{
		LOG("name: %s", tile[i].name.GetString());
		LOG("firstgid: %d", tile[i].firstgid);
		LOG("tile width: %d", tile[i].tilewidth);
		LOG("tile height: %d", tile[i].tileheight);
		LOG("spacing: %d", tile[i].spacing);
		LOG("margin: %d", tile[i].margin);
	}
}
