/*
 * message.hpp
 *
 *  Created on: 13 Aug 2013
 *      Author: Henry J Kupty
 */


#ifndef MESSAGE_
#define MESSAGE_

#include <unistd.h>
#include <algorithm>

namespace message
{
	class msg
	{
	protected:
		char*		val_;
		ssize_t     len_;
			
	public:
		msg() : len_(-1) {}

		msg(const char *bytes, ssize_t nbytes)
		{
			len_ = nbytes;
	        val_ = new char[nbytes];
	        std::copy(bytes, bytes + nbytes, val_);
		}

		~msg()
		{
			delete [] val_;
		}
	};
}

 #endif /* MESSAGE_ */