/*
 * message.hpp
 *
 *  Created on: 13 Aug 2013
 *      Author: Henry J Kupty
 */


#ifndef MESSAGE_
#define MESSAGE_

#include <unistd.h>
#include <string>

namespace message
{
	class msg
	{
	protected:
		char*		val_;
			
	public:
		msg() {}

		msg(void * bytes, size_t nbytes)
		{
	        val_ = static_cast<char *> (malloc(nbytes));
	        memcpy(val_, bytes, nbytes);
		}


		std::string to_string()
		{
			return std::string(val_);
		}
	};
}

 #endif /* MESSAGE_ */