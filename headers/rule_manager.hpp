/*
 * rule_manager.hpp
 *
 *  Created on: 11 Jun 2013
 *      Author: Henry J Kupty
 */

#ifndef RULE_MANAGER_HPP_
#define RULE_MANAGER_HPP_

#include "session.hpp"
#include "external.hpp"

namespace rules
{

	class rule_manager : public external::external
	{
	protected:
		std::string _protocol;

	public:

		virtual void configure(boost::unordered_map<std::string, std::string> kv_) override
		{
			this->_protocol = kv_["protocol"];
		}

				rule_manager () {}
		virtual ~rule_manager() {}
		
		virtual const char* name() = 0;
	};

}
#endif /* RULE_MANAGER_HPP_ */
