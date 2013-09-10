/*
 * tcp_session.cpp
 *
 *  Created on: 12 Aug 2013
 *      Author: Henry J Kupty
 */

 #include "../headers/session.hpp"
 #include "../headers/external.hpp"
 #include "../headers/observable.hpp"

 #include <vector>
 #include <functional>

namespace sessions
{
 class tcp_session : public session
 {

 protected:
 	std::vector<buffer_container*> buffers_;

 public:
 	virtual buffer_data register_mbuffer(buffers::message_buffer* buffer, const char* buff_name) override
 	{
		this->mbuffer_qtd_++;
 		this->mbuffer_inc_++;

 		buffer_data d;
 		d.buffer_id = this->mbuffer_inc_;
 		d.buffer_name = buff_name;

 		buffer_container c;
 		c.buffer = buffer;
 		c.data = d;

 		this->buffers_.push_back(&c);

 		return d;
 	}

 	virtual void deregister_mbuffer(buffer_data d) override
 	{
 		auto it = buffers_.begin();
 		auto pointee = *it;

 		while(pointee->data.buffer_id != d.buffer_id && it != buffers_.end() ) 
		{
			++it;
			pointee = *it;
		}

		this->buffers_.erase(it);
		this->mbuffer_qtd_--;
 	}

 	virtual void start_session()
 	{

 	}

 	buffer_data buffer_for_connection (const char* msg)
 	{
 		buffer_data d;
 		d.buffer_name = msg;

 		auto it = buffers_.begin();
 		auto buff = *it;

 		while(buff->data.buffer_name != d.buffer_name && it != buffers_.end() ) 
		{
			++it;
			buff = *it;
		}

		return buff->data;
 	}

 	tcp_session() { };

 	virtual void put_message_in(const char* msg, buffer_data d) override
 	{
 		auto it = buffers_.begin();
 		auto buff = *it;

 		while(buff->data.buffer_id != d.buffer_id && it != buffers_.end() ) 
		{
			++it;
			buff = *it;
		}

		if (it == buffers_.end())
			return;

 		buff->buffer->in_msg_push(msg);

 		session_data s;

 		s.name_ = this->name_;
 		s.buffer = buff->data;

 		this->notify(IN, s);
 	}

	virtual void put_message_out(const char* msg, buffer_data d) override
 	{
 		auto it = buffers_.begin();
 		auto buff = *it;

 		while(buff->data.buffer_id != d.buffer_id && it != buffers_.end() ) 
		{
			++it;
			buff = *it;
		}

		if (it == buffers_.end())
			return;

 		buff->buffer->out_msg_push(msg);

 		session_data s;

 		s.name_ = this->name_;
 		s.buffer = buff->data;

 		this->notify(OUT, s);
 	}


 	const char* get_message_in(buffer_data bdata)
 	{
 		auto it = buffers_.begin();
 		auto buff = *it;

 		while(buff->data.buffer_id != bdata.buffer_id && it != buffers_.end() ) 
		{
			++it;
			buff = *it;
		}

		if (it == buffers_.end())
			return "";

		return buff->buffer->in_msg_get();

 	}

 	const char* get_message_out(buffer_data bdata)
 	{
 		auto it = buffers_.begin();
 		auto buff = *it;

 		while(buff->data.buffer_id != bdata.buffer_id && it != buffers_.end() ) 
		{
			++it;
			buff = *it;
		}

		if (it == buffers_.end())
			return "";

		return buff->buffer->out_msg_get();
 	}
 };
}

 sessions::session* create_tcp()
 {
 	return new sessions::tcp_session;
 }

 void destroy_tcp(sessions::session* ref)
 {
 	delete ref;
 }

#ifndef API_
#define API_

external::API<sessions::session> api_table = {create_tcp, destroy_tcp};

#endif /* API_*/