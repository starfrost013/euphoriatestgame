/*
Copyright (C) 1997-2001 Id Software, Inc.
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

// game.h -- game dll information visible to server

// DON'T FIX THIS INCLUDE YOU WILL BREAK COMPILING!!!:
#include "../../src/shared/shared.hpp"

#define	GAME_API_VERSION	1

// edict->svflags

#define	SVF_NOCLIENT		0x00000001	// don't send entity to clients, even if it has effects
#define	SVF_DEADMONSTER		0x00000002	// treat as CONTENTS_DEADMONSTER for collision
#define	SVF_MONSTER			0x00000004	// treat as CONTENTS_MONSTER for collision

// edict->solid values

typedef enum
{
	SOLID_NOT,			// no interaction with other objects
	SOLID_TRIGGER,		// only touch when inside, after moving
	SOLID_BBOX,			// touch on edge
	SOLID_BSP			// bsp clip, touch on edge
} solid_t;

//===============================================================

// link_t is only used for entity area links now
typedef struct link_s
{
	struct link_s* prev;
	struct link_s* next;
} link_t;

#define	MAX_ENT_CLUSTERS	16

typedef struct edict_s edict_t;
typedef struct gclient_s gclient_t;

#ifndef GAME_INCLUDE

struct gclient_s
{
	player_state_t	ps;		// communicated by server to clients
	int32_t 		ping;
	// the game dll can add anything it wants after
	// this point in the structure
};


struct edict_s
{
	entity_state_t		s;
	struct gclient_s*	client;
	bool				inuse;
	int32_t 			linkcount;

	// FIXME: move these fields to a server private sv_entity_t
	link_t				area;				// linked to a division node or leaf

	int32_t 			num_clusters;		// if -1, use headnode instead
	int32_t 			clusternums[MAX_ENT_CLUSTERS];
	int32_t 			headnode;			// unused if num_clusters != -1
	int32_t 			areanum, areanum2;

	//================================

	int32_t 			svflags;			// SVF_NOCLIENT, SVF_DEADMONSTER, SVF_MONSTER, etc
	vec3_t				mins, maxs;
	vec3_t				absmin, absmax, size;
	solid_t				solid;
	int32_t 			clipmask;
	edict_t*			owner;

	// the game dll can add anything it wants after
	// this point in the structure
};

#endif		// GAME_INCLUDE

//===============================================================

//
// functions provided by the main engine
//
typedef struct engine_api_s
{
	// special messages
	void	(*bprintf)(int32_t printlevel, const char* fmt, ...);
	void	(*dprintf)(const char* fmt, ...);
	void	(*cprintf)(edict_t* ent, int32_t printlevel, const char* fmt, ...);
	void	(*Text_Draw)(edict_t* ent, const char* font, int32_t x, int32_t y, const char* text, ...);
	void	(*centerprintf)(edict_t* ent, const char* fmt, ...);
	void	(*sound)(edict_t* ent, int32_t channel, int32_t soundindex, float volume, float attenuation, float timeofs);
	void	(*positioned_sound)(vec3_t origin, edict_t* ent, int32_t channel, int32_t soundinedex, float volume, float attenuation, float timeofs);

	// config strings hold all the index strings, the lightstyles,
	// and misc data like the sky definition and cdtrack.
	// All of the current configstrings are sent to clients when
	// they connect, and changes are sent to all connected clients.
	void	(*configstring)(int32_t num, const char* string);

	void	(*error)(const char* fmt, ...);

	// the *index functions create configstrings and some internal server state
	int32_t	(*modelindex)(const char* name);
	int32_t	(*soundindex)(const char* name);
	int32_t	(*imageindex)(const char* name);

	void	(*setmodel)(edict_t* ent, const char* name);

	// collision detection
	trace_t	(*trace)(vec3_t start, vec3_t mins, vec3_t maxs, vec3_t end, edict_t* passent, int32_t contentmask);
	int32_t	(*pointcontents)(vec3_t point);
	bool	(*inPVS)(vec3_t p1, vec3_t p2);
	bool	(*inPHS)(vec3_t p1, vec3_t p2);
	void	(*SetAreaPortalState)(int32_t portalnum, bool open);
	bool	(*AreasConnected)(int32_t area1, int32_t area2);

	// an entity will never be sent to a client or used for collision
	// if it is not passed to linkentity.  If the size, position, or
	// solidity changes, it must be relinked.
	void	(*Edict_Link)(edict_t* ent);
	void	(*Edict_Unlink)(edict_t* ent);		// call before removing an interactive edict
	int32_t	(*BoxEdicts)(vec3_t mins, vec3_t maxs, edict_t** list, int32_t maxcount, int32_t areatype);
	void	(*Player_Move)(pmove_t* pmove);		// player movement code common with client prediction

	// network messaging
	void	(*multicast)(vec3_t origin, multicast_t to);
	void	(*unicast)(edict_t* ent, bool reliable);

	int32_t	(*ReadChar)();
	int32_t	(*ReadByte)();
	int32_t	(*ReadShort)();
	int32_t	(*ReadInt)();
	float	(*ReadFloat)();
	char*	(*ReadString)();
	void	(*ReadPos)(vec3_t vector);	// some fractional bits
	void	(*ReadDir)(vec3_t dir);
	void	(*ReadColor)(color4_t color);
	float	(*ReadAngle)(float f);

	void	(*WriteChar)(int32_t c);
	void	(*WriteByte)(int32_t c);
	void	(*WriteShort)(int32_t c);
	void	(*WriteInt)(int32_t c);
	void	(*WriteFloat)(float f);
	void	(*WriteString)(const char* s);
	void	(*WritePos)(vec3_t pos);	// some fractional bits
	void	(*WriteDir)(vec3_t dir);
	void	(*WriteColor)(color4_t color);
	void	(*WriteAngle)(float f);

	// managed memory allocation
	void*	(*Memory_ZoneMallocTagged)(int32_t size, int32_t tag);
	void	(*Memory_ZoneFree)(void* block);
	void	(*Memory_ZoneFreeTags)(int32_t tag);

	// console variable interaction
	cvar_t* (*Cvar_Get)(const char* var_name, const char* value, int32_t flags);
	cvar_t* (*Cvar_Set)(const char* var_name, const char* value);
	cvar_t* (*Cvar_ForceSet)(const char* var_name, const char* value);

	// ClientCommand and ServerCommand parameter access
	int32_t	(*Cmd_Argc)();
	char*	(*Cmd_Argv)(int32_t n);
	char*	(*Cmd_Args)();	// concatenation of all argv >= 1

	void	(*Cmd_AddCommand)(const char* name, void(*cmd)());
	void	(*Cmd_RemoveCommand)(const char* name);

	// add commands to the server console as if they were typed in
	// for map changing, etc
	void	(*Cbuf_AddText)(const char* text);

	void	(*DebugGraph)(float value, int32_t r, int32_t g, int32_t b, int32_t a);
} engine_api_t;

//
// functions exported by the game subsystem
//
typedef struct game_api_s
{
	int32_t 	api_version;

	// the init function will only be called when a game starts,
	// not each time a level is loaded.  Persistant data for clients
	// and the server can be allocated in init
	void		(*Game_Init)();
	void		(*Game_Shutdown)();

	// each new level entered will cause a call to SpawnEntities
	void		(*Game_SpawnEntities)(char* mapname, char* entstring, char* spawnpoint);

	// Read/Write Game is for storing persistant cross level information
	// about the world state and the clients.
	// WriteGame is called every time a level is exited.
	// ReadGame is called on a loadgame.
	void		(*Game_Write)(char* filename, bool autosave);
	void		(*Game_Read)(char* filename);

	// ReadLevel is called after the default map information has been
	// loaded with SpawnEntities
	void		(*Level_Write)(char* filename);
	void		(*Level_Read)(char* filename);

	bool		(*Client_Connect)(edict_t* ent, char* userinfo);
	void		(*Client_OnConnected)(edict_t* ent);
	void		(*Client_UserinfoChanged)(edict_t* ent, char* userinfo);
	void		(*Client_Disconnect)(edict_t* ent);
	void		(*Client_Command)(edict_t* ent);
	void		(*Client_Event)(edict_t* ent);
	void		(*Client_Think)(edict_t* ent, usercmd_t* cmd);

	void		(*Game_RunFrame)();

	// ServerCommand will be called when an "sv <command>" command is issued on the
	// server console.
	// The game can issue gi.argc() / gi.argv() commands to get the rest
	// of the parameters
	void		(*Server_Command)();

	//
	// global variables shared between game and server
	//

	// The edict array is allocated in the game dll so it
	// can vary in size from one game to another.
	// 
	// The size will be fixed when ge->Init() is called
	edict_t*	edicts;
	int32_t 	edict_size;
	int32_t 	num_edicts;		// current number, <= max_edicts
	int32_t 	max_edicts;
} game_api_t;

extern engine_api_t engine;
extern game_api_t game_export;

game_api_t* Sys_GetGameAPI(engine_api_t* import);
