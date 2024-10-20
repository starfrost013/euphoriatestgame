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
// game_util.cpp
// Required to make the engine work for now. Possibly obsolete
// 20 October 2024

#include <../../src/shared/shared.hpp>
#include <game.hpp>

#ifndef GAME_HARD_LINKED
// this is only here so the functions in q_shared.c and q_shwin.c can link
__declspec(noreturn) void Sys_Error(char* error, ...)
{
	va_list	argptr;
	char	text[1024];

	va_start(argptr, error);
	vsnprintf(text, 1024, error, argptr);
	va_end(argptr);

	engine.error(text);
}

void Com_Printf(const char* msg, ...)
{
	va_list	argptr;
	char	text[1024];

	va_start(argptr, msg);
	vsnprintf(text, 1024, msg, argptr);
	va_end(argptr);

	engine.dprintf(text);
}

#endif
