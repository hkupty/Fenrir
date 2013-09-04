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
	class message_buffer : public external::external
	{

	protected:
		int max_length_;
		const char* name_;
		
	public:

		virtual void configure(boost::unordered_map<std::string,std::string> kv_) override
		{
			this->max_length_ = atoi(kv_["max_length"].c_str()) ?: 1024;
		}

				message_buffer () {};
		virtual ~message_buffer() {};

		virtual bool in_msg_push(const char*) = 0;
		virtual bool out_msg_push(const char*) = 0;

		virtual const char* in_msg_get() = 0;
		virtual const char* out_msg_get() = 0;

	};
}
#endif /* MESSAGE_BUFFER_HPP_ */
