/*
 * message_buffer.hpp
 *
 *  Created on: 11 Jun 2013
 *      Author: Henry J Kupty
 */

#ifndef MESSAGE_BUFFER_HPP_
#define MESSAGE_BUFFER_HPP_

#include "fix_message.hpp"

namespace buffers
{

	typedef void (*process_message)(fix::fix_message*);

	class message_buffer
	{
	public:
		message_buffer();
		virtual ~message_buffer() = 0;

		virtual void push_message(fix::fix_message*) = 0;
		virtual void process_callback(process_message*) = 0;
	};

	struct API
	{
		message_buffer* (*create)(void);
		void (*destroy)(message_buffer*);
	};

}
#endif /* MESSAGE_BUFFER_HPP_ */
