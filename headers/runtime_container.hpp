/*
 * runtime_container.hpp
 *
 *  Created on: 26 Aug 2013
 *      Author: Henry J Kupty
 */

 #ifndef RUNTIME_CONTAINER_HPP_
 #define RUNTIME_CONTAINER_HPP_

 #include "di_container.hpp"

 #include "message_buffer.hpp"
 #include "rule_manager.hpp"
 #include "session.hpp"
 #include "session_manager.hpp"
 #include "config.hpp"
 #include "external.hpp"

 #include "network_container.hpp"

 #include "../core/di_container.cpp"

 
 class runtime_container
 {
		di_container<rules::rule_manager, external::API<rules::rule_manager>> rulesdi_;
		di_container<sessions::session, external::API<sessions::session>> sessiondi_;
		di_container<buffers::message_buffer, external::API<buffers::message_buffer>> bufferdi_;
		di_container<session_ms::session_manager, external::API<session_ms::session_manager>> smanagerdi_;

		network_container* network;

 public:
 	runtime_container(){}
 	~runtime_container(){}

 	bool load(cfg::config_t);

 	void register_network(network_container*);

 	//void unload();

 };
 #endif /* RUNTIME_CONTAINER_HPP_*/