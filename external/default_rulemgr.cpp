/*
 * default_rulemgr.cpp
 *
 *  Created on: 14 Jun 2013
 *      Author: Henry J Kupty
 */

#include "../headers/rule_manager.hpp"

class default_rulemgr : public rules::rule_manager
{

const char* name() override
{
	return "Default";
}

};


rules::rule_manager* create_default()
{
	return new default_rulemgr;
}

void destroy_default(rules::rule_manager* r)
{
	delete r;
}

rules::API api_table = {create_default, destroy_default};
