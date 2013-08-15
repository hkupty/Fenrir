/*
 * message.hpp
 *
 *  Created on: 13 Aug 2013
 *      Author: Henry J Kupty
 */


#ifndef MESSAGE_
#define MESSAGE_

#include <cstddef>

namespace message
{
	class msg
	{
	protected:
		const char* _msg_val;
		std::size_t _msg_size;
		short	 	_msg_len;
		short		_msg_chksum;
	
	public:
		virtual void set_field();

		msg(char* val_) : _msg_val(static_cast<const char*>(val_)) {};

	};
}

 #endif /* MESSAGE_ */