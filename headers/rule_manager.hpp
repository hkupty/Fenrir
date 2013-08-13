/*
 * rule_manager.hpp
 *
 *  Created on: 11 Jun 2013
 *      Author: Henry J Kupty
 */

#ifndef RULE_MANAGER_HPP_
#define RULE_MANAGER_HPP_

#include "session.hpp"

namespace rules
{

	class rule_manager
	{
	public:
				rule_manager () {}
		virtual ~rule_manager() {}
		
		virtual const char* name() = 0;
	};

	struct API
	{
		rule_manager* 	(*create)	(void);
		void 			(*destroy)	(rule_manager*);
	};
}
#endif /* RULE_MANAGER_HPP_ */
