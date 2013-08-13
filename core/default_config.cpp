/*
 * default_config.cpp
 *
 *  Created on: 10 Jun 2013
 *      Author: Henry J Kupty
 */

#include <sstream>
#include <stdio.h>

#include "../headers/default_config.hpp"
#include "../headers/log.hpp"

const std::string k_cfg = std::string(_log::_bold + "[CONFIG    ]" + _log::_clr);

namespace cfg
{
	const char*	GLOBAL = "global_cfg";
	std::string _NAME = "_name";
	std::string _TYPE = "_type";

	config_t default_config::get_config_cfg(int _lvl, lua_State* L)
	{
		config_t config_node(_lvl);

		lua_pushnil(L);
		while (lua_next(L, LUA_STACK_KEY) != 0)
		{
			if(lua_istable(L, LUA_STACK_VALUE))
			{
				config_node._underlying.push_back(get_config_cfg(_lvl + 1, L));
			}
			else if(lua_isstring(L,LUA_STACK_VALUE))
			{
				std::string key = std::string(lua_tostring(L,LUA_STACK_KEY));
				std::string val = std::string(lua_tostring(L,LUA_STACK_VALUE));

				if(_NAME.compare(key) == 0) config_node._name = val;
				
				else if (_TYPE.compare(key) == 0) config_node._type = val;

				else config_node._kv[key] = val;
				
			}

			lua_pop(L, 1);
		}

		return config_node;
	}


	//Exec Environment --> config_file.lua
	config_t default_config::get_config()
	{
		lua_State* L = this->container.get_state();

		if(this->container.run_file_multret("config.lua"))
		{
			lua_getglobal(L, GLOBAL);

			if (lua_istable(L,LUA_STACK_VALUE))
			{
				lua_pushnil(L);
				return this->get_config_cfg(0, L);
			}
		}
		std::cout << _log::_err <<  k_cfg << "ERROR WHILE LOADING CONFIG, EXITING" << std::endl;
		exit(EXIT_FAILURE);
	}
}