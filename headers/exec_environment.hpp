/*
 * exec_environment.hpp
 *
 *  Created on: 11 Jun 2013
 *      Author: Henry J Kupty
 */

#ifndef EXEC_ENVIRONMENT_HPP_
#define EXEC_ENVIRONMENT_HPP_

#include <iostream>
#include "network_container.hpp"
#include "runtime_container.hpp"
#include "config.hpp"

namespace exec
{

	class exec_environment
	{
		cfg::config cfg_;

		std::string server_name_;

		network_container* current_network_;

		runtime_container* current_runtime_;

	public:
				exec_environment () {};
		virtual ~exec_environment();
		void start();
	};
}
#endif /* EXEC_ENVIRONMENT_HPP_ */
