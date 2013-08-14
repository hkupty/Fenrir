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

namespace buffers
{

	typedef void (*process_message)(message::msg*);

	class message_buffer : public external::external
	{
		
	public:
		message_buffer();
		virtual ~message_buffer() = 0;

		virtual void push_message(message::msg*) = 0;
	};

	class async_message_buffer : public message_buffer
	{

	protected:
		process_message _callback;
		int				_tqtd;

	public:
		virtual void configure(boost::unordered_map<std::string,std::string> kv_) override
		{
			this->_tqtd = atoi(kv_["thread_qtd"].c_str());
		}

		virtual void register_callback(process_message) = 0;
		virtual void asyc_process() = 0;
	};
}
#endif /* MESSAGE_BUFFER_HPP_ */
