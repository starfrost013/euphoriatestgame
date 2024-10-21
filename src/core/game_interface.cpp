/*
Euphoria Game Engine
Copyright (C) 2023-2024 starfrost

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

*/
// game_interface.cpp
// Loads the game interface.
// Required to make the engine work for now. Possibly obsolete
// 20 October 2024

#include "game.hpp"
#include "game_local.hpp"

engine_api_t engine;				// Functions imported from the engine.
game_api_t game_export;			// Functions exported to the engine.

//
// globals
//
edict_t*	game_edicts;
int32_t 	edict_size;
int32_t 	num_edicts;				// current number, <= max_edicts
int32_t 	max_edicts;

//
// TEMPORARY FUNCTIONS
// UNTIL THERE IS ACTUAL FUNCTIONALITY!!!
// 

// the init function will only be called when a game starts,
// not each time a level is loaded.  Persistant data for clients
// and the server can be allocated in init
void Game_Init() {};
void Game_Shutdown() {};

// each new level entered will cause a call to SpawnEntities
void Game_SpawnEntities(char* mapname, char* entstring, char* spawnpoint) {};

// Read/Write Game is for storing persistant cross level information
// about the world state and the clients.
// WriteGame is called every time a level is exited.
// ReadGame is called on a loadgame.
void Game_Write(char* filename, bool autosave) {};
void Game_Read(char* filename) {};

// ReadLevel is called after the default map information has been
// loaded with SpawnEntities
void Level_Write(char* filename) {};
void Level_Read(char* filename) {};

bool Client_Connect(edict_t* ent, char* userinfo) { return true; };
void Client_OnConnected(edict_t* ent) {};
void Client_UserinfoChanged(edict_t* ent, char* userinfo) {};
void Client_Disconnect(edict_t* ent) {};
void Client_Command(edict_t* ent) {};
void Client_Event(edict_t* ent) {};
void Client_Think(edict_t* ent, usercmd_t* cmd) {};

void Game_RunFrame() {};

void Server_Command() {};

game_api_t* Sys_GetGameAPI(engine_api_t* game_import)
{
	engine = *game_import;

	game_export.api_version = GAME_API_VERSION;

	// edict stuf
	// hardcode max_edicts - maybe make it extensible later;
	game_export.max_edicts = MAX_EDICTS;
	game_export.edict_size = sizeof(edict_t);
	game_edicts = (edict_t*)engine.Memory_ZoneMallocTagged(sizeof(edict_t) * max_edicts, TAG_GAME);
	game_export.edicts = game_edicts;
	game_export.num_edicts = 0;

	game_export.Client_Command = Client_Command;
	game_export.Client_Connect = Client_Connect;
	game_export.Client_Disconnect = Client_Disconnect;
	game_export.Client_Event = Client_Event;
	game_export.Client_OnConnected = Client_OnConnected;
	game_export.Client_Think = Client_Think;
	game_export.Client_UserinfoChanged = Client_UserinfoChanged;

	game_export.Game_Init = Game_Init;
	game_export.Game_Read = Game_Read;
	game_export.Game_RunFrame = Game_RunFrame;
	game_export.Game_Shutdown = Game_Shutdown;
	game_export.Game_SpawnEntities = Game_SpawnEntities;
	game_export.Game_Write = Game_Write;

	game_export.Level_Read = Level_Read;
	game_export.Level_Write = Level_Write;

	game_export.Server_Command = Server_Command;

	return &game_export;
}
