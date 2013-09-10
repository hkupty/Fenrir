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
	struct buffer_data
	{
		short buffer_id;
		const char* buffer_name;
	};

	struct buffer_container
	{
		buffer_data data;
		buffers::message_buffer* buffer;
	};

	struct session_data
	{
		buffer_data buffer;
		const char* name_;
		
	};

	class session : public external::external, public multi_channel_observable<session_data>
	{
	protected:
		const char*		name_;
		const char*		group_;
		short			mbuffer_qtd_;
		short 			mbuffer_inc_;
		int				port_;

	public:

		virtual void configure(boost::unordered_map<std::string,std::string> _kv) override
		{
			this->group_ = _kv["group"].c_str();
			this->port_ = atoi(_kv["port"].c_str());

		}

		virtual void set_name(std::string name)
		{
			this->name_ = name.c_str();
		}

		virtual void start_session() = 0;

				session () {};
		virtual ~session() {};

		virtual buffer_data register_mbuffer(buffers::message_buffer*, const char*) = 0;
		virtual void deregister_mbuffer(buffer_data) = 0;

		virtual void put_message_in(const char*, buffer_data) = 0;
		virtual void put_message_out(const char*, buffer_data) = 0;

		virtual const char* get_message_in(buffer_data) =0;
		virtual const char* get_message_out(buffer_data) =0;

	};

}
#endif /* SESSION_HPP_ */
