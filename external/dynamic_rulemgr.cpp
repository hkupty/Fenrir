/*
 * default_rulemgr.cpp
 *
 *  Created on: 14 Jun 2013
 *      Author: Henry J Kupty
 */

#include "../headers/rule_manager.hpp"

class dynamic_rulemgr : public rules::rule_manager
{


	const char* name()
	{
		return "Dynamic";
	}
	
};


rules::rule_manager* create_dynamic()
{
	return new dynamic_rulemgr;
}

void destroy_dynamic(rules::rule_manager* r)
{
	delete r;
}

rules::API api_table = {create_dynamic, destroy_dynamic};
