#include "p2Defs.h"
#include "j1App.h"
#include "p2Log.h"
#include "j1FileSystem.h"
#include "SDL/include/SDL_rwops.h"
#include "SDL/include/SDL_filesystem.h"
#include "PhysFS/include/physfs.h"

#pragma comment( lib, "PhysFS/libx86/physfs.lib" )

j1FileSystem::j1FileSystem(const char* game_path) : j1Module()
{
	name.create("file_system");

	// TODO 1: Init PhysFS lib
	PHYSFS_init(NULL);
	
	// TODO 2: Mount directory ".", then mount "data.zip"
	// files in the folder should take precendence over the zip file!
	PHYSFS_mount(".", NULL , 1);
	PHYSFS_mount("data.zip", NULL, 0);
}

// Destructor
j1FileSystem::~j1FileSystem()
{
	// TODO 1: stop PhysFS lib
	PHYSFS_deinit();
}

// Called before render is available
bool j1FileSystem::Awake()
{
	LOG("Loading File System");
	bool ret = true;

	// This is a good place to setup the write dir (homework)

	return ret;
}

// Read a whole file and put it in a new buffer
unsigned int j1FileSystem::Load(const char* file, char** buffer) const
{
	unsigned int ret = 0;

	// TODO 3: Read a file and allocate needed bytes to buffer and write all data into it
	// return the size of the data
	PHYSFS_File* file_load= PHYSFS_openRead(file);

	if(file_load == 0)
		LOG("PHYSFS LoadFile Error: %s\n", PHYSFS_getLastError());
	
	PHYSFS_sint64 size = PHYSFS_fileLength(file_load);
	

	if(size > 0)
		LOG("PHYSFS fileLenght Error: %s\n", PHYSFS_getLastError());

	*buffer = new char[(uint)size];
	PHYSFS_sint64 read_file = PHYSFS_read(file_load, *buffer, 1, (PHYSFS_sint32)size);

	if (read_file != size)
	{
		LOG("PHYSFS read Error: %s\n", PHYSFS_getLastError());
		RELEASE(buffer);
	}
	else
		ret = (uint)read_file;

	return ret;
}

// Read a whole file and put it in a new buffer
SDL_RWops* j1FileSystem::Load(const char* file) const
{
	// TODO 4: Using our previous Load method
	// create a sdl rwops using SDL_RW_From_ConstMem()
	// and return it if everything goes well
	SDL_RWops* ret_rw = nullptr;
	char* buffer = nullptr;
	unsigned int size = Load(file, &buffer);
	ret_rw = SDL_RWFromConstMem(buffer, size);

	if (ret_rw != NULL)
		ret_rw->close = close_sdl_rwops;
	
	return ret_rw;;
}


//HW
bool j1FileSystem::Exist(const char* path)
{
	bool ret = false;

	if (PHYSFS_exists(path) != 0)
		ret = true;

	return ret;
}

/*
PHYSFS_sint64 j1FileSystem::SizeFile(PHYSFS_File* file)
{
	return PHYSFS_fileLength(file);
}
*/

void j1FileSystem::Delete(SDL_RWops *rw)
{
	RELEASE(rw->hidden.mem.base);
	SDL_FreeRW(rw);
}

// TODO 4: you will need to use this small helper function
// to make sure all data is freed automatically
int close_sdl_rwops(SDL_RWops *rw)
{
	RELEASE(rw->hidden.mem.base);
	SDL_FreeRW(rw);
	return 0;
}

