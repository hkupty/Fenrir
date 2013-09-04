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
#include "observable.hpp"
#include <string>
#include <cstdlib>
#include <iostream>

namespace sessions
{

	// const short READ_ACCESS 	= 0x01 << 0;
	// const short WRITE_ACCESS 	= 0x01 << 1;

	struct buffer_data
	{
		short buffer_id;
	};

	class session : public external::external //public observable<session>
	{
	protected:
		std::string		name_;
		std::string		group_;
		short			mbuffer_qtd_;
		short 			mbuffer_inc_;
		int				port_;

	public:

		virtual void configure(boost::unordered_map<std::string,std::string> kv_) override
		{
			this->group_ = kv_["group"];
			this->port_ = atoi(kv_["port"].c_str());

		}

		virtual void set_name(std::string name)
		{
			this->name_ = name;
		}

		virtual void start_session() = 0;

				session () {};
		virtual ~session() {};

		virtual buffer_data register_mbuffer(buffers::message_buffer*) = 0;
		virtual void deregister_mbuffer(buffer_data) = 0;

	};

}
#endif /* SESSION_HPP_ */
