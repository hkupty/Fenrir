/*
 * basic_session_manager.cpp
 *
 *  Created on: 10 Aug 2013
 *      Author: Henry J Kupty
 */

 #include "../headers/session_manager.hpp"
 #include "../headers/external.hpp"
 #include <boost/container/list.hpp>


class basic_session_manager : public session_ms::session_manager
{

	protected:
		boost::container::list<sessions::session*> sessions_;
		rules::rule_manager* rmanager_;

	public:

	virtual void register_session(sessions::session* _session) override
	{
		this->sessions_.push_back(_session);
	}

	virtual void deregister_session(sessions::session* _session) override
	{
		this->sessions_.remove(_session);
	}

	virtual void register_rule_manager(rules::rule_manager* _rmanager) override
	{
		this->rmanager_ = _rmanager;
	}
};


session_ms::session_manager* create_basic()
{
	return new basic_session_manager;
}

void destroy_basic(session_ms::session_manager* ref)
{
	delete ref;
}

external::API<session_ms::session_manager> api_table = {create_basic, destroy_basic};
