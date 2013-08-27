/*
 * runtime_container.cpp
 *
 *  Created on: 26 Aug 2013
 *      Author: Henry J Kupty
 */

 #include "../headers/runtime_container.hpp"

 #include <vector>

 const std::string k_env = std::string(_log::_bold + "[RUNTIME   ]" + _log::_clr);
 const std::string k_rmanager = std::string("rule_alg");

 bool runtime_container::load(cfg::config_t cfg_node)
 {
 	std::cout << _log::_inf << k_env << "STARTING SESSION MANAGER OF TYPE " << cfg_node._type << std::endl;

	session_ms::session_manager* smanager = this->smanagerdi_.create_t(cfg_node._type);

	std::cout << _log::_scc << k_env << "SESSION MANAGER STARTED" << std::endl;

	if (cfg_node._kv.find(k_rmanager) == cfg_node._kv.end()) 
	{
		std::cout << _log::_err << k_env << "UNABLE TO FIND RULE MANAGER KEY IN CFG, EXITING" << std::endl;
		return false;
	}

	std::string rule_alg = cfg_node._kv[k_rmanager];

	rules::rule_manager* r = rulesdi_.create_t(rule_alg);

	r->configure(cfg_node._kv);

	std::cout << _log::_inf << k_env << "USING RULE MANAGER " << r->name() << std::endl;	


	if (r == NULL)
	{
		std::cout << _log::_err << k_env << "UNABLE TO START RULE MANAGER, EXITING" << std::endl;	
		return false;
	}

	std::cout << _log::_inf << k_env << "LINKING RULE MANAGER TO SESSION MANAGER" << std::endl;	

	smanager->register_rule_manager(r);

	std::cout << _log::_scc << k_env << "RULE MANAGER LINKED" << std::endl;	

	for (auto session_it = cfg_node._underlying.begin(); session_it != cfg_node._underlying.end(); session_it++)
	{
		sessions::session* s = sessiondi_.create_t(session_it->_type);

		s->configure(session_it->_kv);
		s->set_name(session_it->_name);

		smanager->register_session(s);
		for (auto buffer_it = session_it->_underlying.begin(); buffer_it != session_it->_underlying.end(); buffer_it++ )
		{
			buffers::message_buffer* mb = bufferdi_.create_t(buffer_it->_type);
			s->register_mbuffer(mb);
			mb->configure(buffer_it->_kv);
		}
	}

	return true;
 }

 void runtime_container::register_network(network_container* net)
 {
 	this->network = net;
 }