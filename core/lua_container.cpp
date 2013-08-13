/*
 * lua_container.cpp
 *
 *  Created on: 10 Jun 2013
 *      Author: Henry J Kupty
 */

#include "../headers/lua_container.hpp"

#include <iostream>

lua_container::lua_container()
{
	const luaL_Reg lualibs[] =
	{
		{ "base", luaopen_base },
		{ "table", luaopen_table },
		{ NULL, NULL}
	};

	this->lib = lualibs;
	this->lua_state = luaL_newstate();

	this->init_state();
}

lua_State* lua_container::get_state()
{
	return this->lua_state;
}

bool lua_container::run_file_multret(const char* filename)
{
	int loadfile = luaL_loadfile(this->lua_state, filename);
	int result = 0;
	if(loadfile == LUA_OK)
		result	= lua_pcall(this->lua_state, 0, LUA_MULTRET,0);
	else
		return false;
	 return result == LUA_OK;
}
