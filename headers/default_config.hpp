
/*
 * default_config.hpp
 *
 *  Created on: 10 Jun 2013
 *      Author: Henry J Kupty
 */

#ifndef DEFAULT_CONFIG_HPP_
#define DEFAULT_CONFIG_HPP_

#include "lua_container.hpp"
#include <boost/unordered_map.hpp>
#include <boost/container/list.hpp>
#include <iostream>
#include <vector>


namespace cfg
{
	struct config_t
	{
		int _level;
		std::string _name;
		std::string _type;
		boost::unordered_map<std::string, std::string> _kv;
		boost::container::list<config_t> _underlying;

		config_t() : _level(0) {}
		config_t(int _lvl) : _level(_lvl) {}

	};

	class default_config
	{
		lua_container container;

		config_t config;

	protected:
		config_t get_config_cfg	(int, lua_State*);

	public:
		config_t get_config();

				default_config () {};
		virtual ~default_config() {};
	};
}	// namespace cfg

#endif /* DEFAULT_CONFIG_HPP_ */
