/*
 * session.hpp
 *
 *  Created on: 12 Jun 2013
 *      Author: Henry J Kupty
 */

#ifndef SESSION_HPP_
#define SESSION_HPP_

#include "message_buffer.hpp"
#include "external.hpp"
#include <string>

namespace sessions
{

	// const short READ_ACCESS 	= 0x01 << 0;
	// const short WRITE_ACCESS 	= 0x01 << 1;

	class session : public external::external
	{
	protected:
		std::string		_session_name;
		std::string		_session_group;
		
		//short			_session_accesslevel;
		short			_session_mbuffer_qtd;

	public:

		virtual void configure(boost::unordered_map<std::string,std::string> kv_) override
		{
			this->_session_group = kv_["group"];
			// std::string acc = kv_["access"];
			// this->_session_accesslevel = acc != "" ?: WRITE_ACCESS;
		}

				session () {};
		virtual ~session() {};

		virtual void register_mbuffer(buffers::message_buffer*) = 0;
		virtual void deregister_mbuffer(buffers::message_buffer*) = 0;

	};

}
#endif /* SESSION_HPP_ */
