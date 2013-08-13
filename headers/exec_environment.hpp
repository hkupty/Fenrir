/*
 * exec_environment.hpp
 *
 *  Created on: 11 Jun 2013
 *      Author: Henry J Kupty
 */

#ifndef EXEC_ENVIRONMENT_HPP_
#define EXEC_ENVIRONMENT_HPP_

#include <iostream>
#include "message_buffer.hpp"
#include "rule_manager.hpp"
#include "di_container.hpp"
#include "session.hpp"
#include "session_manager.hpp"
#include "default_config.hpp"

#include "../core/di_container.cpp"


namespace exec
{

	const std::string k_rmanager = std::string("rule_alg");

	class exec_environment
	{
		cfg::default_config config;

		std::string server_name;

		di_container<rules::rule_manager, rules::API> _rulesdi;
		di_container<sessions::session, sessions::API> _sessiondi;
		di_container<buffers::message_buffer, buffers::API> _bufferdi;
		di_container<session_ms::session_manager, session_ms::API> _smanagerdi;

	public:
				exec_environment () {};
		virtual ~exec_environment() {};
		void start();
	};
}
#endif /* EXEC_ENVIRONMENT_HPP_ */
