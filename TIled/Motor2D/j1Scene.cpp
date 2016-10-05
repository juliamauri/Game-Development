#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Textures.h"
#include "j1Audio.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1Map.h"
#include "j1Scene.h"

#include <string>

j1Scene::j1Scene() : j1Module()
{
	name.create("scene");
}

// Destructor
j1Scene::~j1Scene()
{}

// Called before render is available
bool j1Scene::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool j1Scene::Start()
{
	App->map->Load("orthogonal-outside.tmx");
	return true;
}

// Called each loop iteration
bool j1Scene::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool j1Scene::Update(float dt)
{
	if(App->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN)
		App->LoadGame("save_game.xml");

	if(App->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN)
		App->SaveGame("save_game.xml");

	if(App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
		App->render->camera.y -= 1;

	if(App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
		App->render->camera.y += 1;

	if(App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		App->render->camera.x -= 1;

	if(App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		App->render->camera.x += 1;

	//App->render->Blit(img, 0, 0);
	App->map->Draw();

	p2SString title("Map:");
	std::string numbers;
	
	// TODO 7: Set the window title like
	// "Map:%dx%d Tiles:%dx%d Tilesets:%d"

	numbers = std::to_string(App->map->map.width);
	title += numbers.c_str();
	title += "x";
	numbers = std::to_string(App->map->map.height);
	title += numbers.c_str();

	title += " Tiles:";
	numbers = std::to_string(App->map->map.tilewidth);
	title += numbers.c_str();
	title += "x";
	numbers = std::to_string(App->map->map.tileheight);
	title += numbers.c_str();

	title += " Tilesets:";
	numbers = std::to_string(App->map->tilesets.count());
	title += numbers.c_str();

	int x = 0;
	int y = 0;
	App->input->GetMousePosition(x, y);

	p2Point<uint> TilePos = App->map->GetTilePos(x, y);

	title += " Tile:";
	numbers = std::to_string(TilePos.x);
	title += numbers.c_str();
	title += "x";
	numbers = std::to_string(TilePos.y);
	title += numbers.c_str();

	App->win->SetTitle(title.GetString());

	return true;
}

// Called each loop iteration
bool j1Scene::PostUpdate()
{
	bool ret = true;

	if(App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	return ret;
}

// Called before quitting
bool j1Scene::CleanUp()
{
	LOG("Freeing scene");

	return true;
}
