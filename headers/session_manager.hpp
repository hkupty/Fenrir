/*
 * session_manager.hpp
 *
 *  Created on: 06 Aug 2013
 *      Author: Henry J Kupty
 */

#ifndef SESSION_MANAGER_HPP_
#define SESSION_MANAGER_HPP_

#include "session.hpp"
#include "rule_manager.hpp"

namespace session_ms
{

	class session_manager
	{

	public:
			session_manager () {}
	virtual ~session_manager() {}

	virtual void register_session(sessions::session*) = 0 ;
	virtual void deregister_session(sessions::session*) = 0 ;
	virtual void register_rule_manager(rules::rule_manager*) = 0 ;

};

}
#endif /* SESSION_MANAGER_HPP_ */
