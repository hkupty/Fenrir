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
#include <cstdlib>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

namespace sessions
{

	// const short READ_ACCESS 	= 0x01 << 0;
	// const short WRITE_ACCESS 	= 0x01 << 1;

	class session : public external::external
	{
	protected:
		std::string		_session_name;
		std::string		_session_group;
		short			_session_mbuffer_qtd;

	public:

		virtual void configure(boost::unordered_map<std::string,std::string> kv_) override
		{
			this->_session_group = kv_["group"];
		}

		virtual void start_session(boost::asio::io_service& io, int port) = 0;
		

				session () {};
		virtual ~session() {};

		virtual void register_mbuffer(buffers::message_buffer*) = 0;
		virtual void deregister_mbuffer(buffers::message_buffer*) = 0;

	};

}
#endif /* SESSION_HPP_ */
