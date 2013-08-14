/*
 * default_rulemgr.cpp
 *
 *  Created on: 14 Jun 2013
 *      Author: Henry J Kupty
 */

 #include "../headers/rule_manager.hpp"
 #include "../headers/external.hpp"

class default_rulemgr : public rules::rule_manager
{

	void configure(boost::unordered_map<std::string, std::string> kv_) override
	{
		rules::rule_manager::configure(kv_);
	}



	const char* name() override
	{
		return (std::string("Default with protocol ") + this->_protocol).c_str();
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

external::API<rules::rule_manager> api_table = {create_default, destroy_default};
