/*
 * default_rulemgr.cpp
 *
 *  Created on: 14 Jun 2013
 *      Author: Henry J Kupty
 */

 #include "../headers/rule_manager.hpp"
 #include "../headers/external.hpp"

class dynamic_rulemgr : public rules::rule_manager
{

	void configure(boost::unordered_map<std::string, std::string> kv_) override
	{
		rules::rule_manager::configure(kv_);
	}


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

external::API<rules::rule_manager> api_table = {create_dynamic, destroy_dynamic};
