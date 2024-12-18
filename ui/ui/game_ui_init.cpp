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

// game_ui_init.cpp: Initialises the GameUI interface and UI
// 21 October 2024

#include <game_ui.hpp>
#include <game_ui_local.hpp>

game_ui_api_t game_ui;
engine_ui_api_t engine;

game_ui_api_t* GameUI_Init(engine_ui_api_t* engine_api)
{
	engine = *engine_api;

	game_ui.version = GAME_UI_INTERFACE_VERSION;
	game_ui.GameUI_Create = GameUI_Create;


	//engine.dprintf("------- GameUI interface initialised -------");

	
	return &game_ui;
}

bool GameUI_Create()
{
	//engine.dprintf("------- Creating Game UI -------");
	//engine.dprintf("------- Game UIs created -------");
	return true; 
}