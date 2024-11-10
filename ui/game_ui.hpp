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
#pragma once
// DON'T FIX THIS! MULTIPLE MODULES DEPEND ON THIS FILE!
#include "../../src/shared/shared.hpp"
#include "../../src/client/include/ui_game_interface.hpp"

// game_ui.hpp
// Game Client/UI DLL core header
// 21 October 2024

// the version of the game ui interface
#define GAME_UI_INTERFACE_VERSION	1

// the game UI interface object
typedef struct game_ui_api_s
{
	uint32_t version;

	bool	(*GameUI_Create)();
} game_ui_api_t;

game_ui_api_t* GameUI_Init(engine_ui_api_t* engine_ui_api);
bool GameUI_Create();