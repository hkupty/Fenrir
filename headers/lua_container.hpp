/*
 * lua.hpp
 *
 *  Created on: 10 Jun 2013
 *      Author: Henry J Kupty
 */

#ifndef LUA_CONTAINER_H_
#define LUA_CONTAINER_H_

#include "lua/lua.hpp"

const int LUA_STACK_KEY = -2;
const int LUA_STACK_VALUE = -1;

class lua_container
{
	lua_State *lua_state;
	const luaL_Reg *lib;

protected:
	void init_state()
	{
		for(; lib->func != NULL; lib++)
		{
			lib->func(lua_state);
			lua_settop(lua_state, 0);
		}
	}

public:

	lua_State* get_state();
	bool run_file_multret(const char*);

			lua_container ();
	virtual ~lua_container() {};
};


#endif /* LUA_CONTAINER_H_ */
