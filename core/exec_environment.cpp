/*
 * exec_environment.cpp
 *
 *  Created on: 16 Jun 2013
 *      Author: Henry J Kupty
 */

#include "../headers/exec_environment.hpp"
#include "../headers/default_config.hpp"
#include "../headers/rule_manager.hpp"
#include "../headers/session_manager.hpp"
#include "../headers/log.hpp"
#include <vector>

const std::string k_env = std::string(_log::_bold + "[RUNTIME   ]" + _log::_clr);

void exec::exec_environment::start()
{
	std::cout << _log::_inf <<  k_env << "CONFIG LOAD" << std::endl;

	cfg::config_t cfg = this->config.get_config();

	std::cout << _log::_scc << k_env << "CONFIG LOADED" << std::endl;

	this->server_name = cfg._name;

	std::cout << _log::_inf << k_env << "STARTING SERVER AS " << this->server_name << std::endl;

	std::cout << _log::_inf << k_env << "STARTING SESSION MANAGER OF TYPE " << cfg._type << std::endl;

	session_ms::session_manager* smanager = _smanagerdi.create_t(cfg._type);

	std::cout << _log::_scc << k_env << "SESSION MANAGER STARTED" << std::endl;

	if (cfg._kv.find(k_rmanager) == cfg._kv.end()) 
	{
		std::cout << _log::_err << k_env << "UNABLE TO FIND RULE MANAGER KEY IN CFG, EXITING" << std::endl;
		exit(EXIT_FAILURE);
	}

	std::string rule_alg = cfg._kv[k_rmanager];

	rules::rule_manager* r = _rulesdi.create_t(rule_alg);

	std::cout << _log::_inf << k_env << "USING RULE MANAGER " << r->name() << std::endl;	


	if (r == NULL)
	{
		std::cout << _log::_err << k_env << "UNABLE TO START RULE MANAGER, EXITING" << std::endl;	
		exit(EXIT_FAILURE);	
	}

	std::cout << _log::_inf << k_env << "LINKING RULE MANAGER TO SESSION MANAGER" << std::endl;	

	smanager->register_rule_manager(r);

	std::cout << _log::_scc << k_env << "RULE MANAGER LINKED" << std::endl;	

	for (auto session_it = cfg._underlying.begin(); session_it != cfg._underlying.end(); session_it++)
	{
		std::cout << _log::_inf << k_env << "------------------------------------------"<< std::endl;			
		std::cout << _log::_inf << k_env << session_it->_name << ", " << session_it->_type << std::endl;	
		sessions::session* _s = _sessiondi.create_t(session_it->_type);
		smanager->register_session(_s);
		for (auto buffer_it = session_it->_underlying.begin(); buffer_it != session_it->_underlying.end(); buffer_it++ )
		{
			std::cout << _log::_inf << k_env << buffer_it->_name << ", " << buffer_it->_type << std::endl;			
		}
		std::cout << _log::_inf << k_env << "------------------------------------------"<< std::endl;			
	}


	std::cout << _log::_inf << k_env << "EXITING" << std::endl;
}
