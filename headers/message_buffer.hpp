/*
 * message_buffer.hpp
 *
 *  Created on: 11 Jun 2013
 *      Author: Henry J Kupty
 */

#ifndef MESSAGE_BUFFER_HPP_
#define MESSAGE_BUFFER_HPP_

#include "message.hpp"
#include "external.hpp"

#include <cstdlib>
#include <iostream>

namespace buffers
{
	typedef void (*process_message)(message::msg*);

	class message_buffer : public external::external
	{
	protected:
		int max_length_;
		
	public:

		virtual void configure(boost::unordered_map<std::string,std::string> kv_) override
		{
			this->max_length_ = atoi(kv_["max_length"].c_str()) ?: 1024;
		}
				message_buffer () {};
		virtual ~message_buffer() {};

		virtual bool push_message(message::msg*) = 0;
	};
}
#endif /* MESSAGE_BUFFER_HPP_ */
