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
 	
 	buffers_::iterator find_buffer(buffer_data d)
 	{
 		


 		if(it == buffers_.end())
 			return nullptr;

 		return pointee;
 	}

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

		return buff;
 	}

 	tcp_session() { };

 	virtual void put_message_in(const char* msg, buffer_data data)
 	{
 		auto it = buffers_.begin();
 		auto buff = *it;

 		while(buff->data.buffer_id != d.buffer_id && it != buffers_.end() ) 
		{
			++it;
			buff = *it;
		}

 		buff->buffer->in_msg_push(msg);

 		session_data s;

 		s.name_ = this->name_;
 		s.buffer = buff->data;

 		this->notify(IN, s);
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