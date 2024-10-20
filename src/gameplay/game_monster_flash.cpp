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
// game_monster_flash.c
// Required to make the engine work for now. Obsolete.
// 20 October 2024


// this file is included in both the game dll and engine,
// the game needs it to source shot locations, the client
// needs it to position muzzle flashes
// DON'T FIX THIS INCLUDE YOU WILL BREAK COMPILING!!!:

#include "../../../src/shared/shared.hpp"

vec3_t monster_flash_offset[] =
{
	0.0, 0.0, 0.0,				//start
	0.0, 0.0, 0.0,				//end
};
