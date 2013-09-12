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
//TODO: Gotta free it all
 protected:
 	std::vector<buffer_container*> buffers_;

 public:
 	virtual void register_mbuffer(buffers::message_buffer* buffer, const char* buff_name) override
 	{
		++mbuffer_qtd_;
 		++mbuffer_inc_;

 		std::cout<<"Register:"<< mbuffer_qtd_ << "," << mbuffer_inc_ << std::endl;

 		buffer_data* d = new buffer_data(mbuffer_inc_,buff_name);

 		buffer_container* c = new buffer_container(d, buffer);

 		this->buffers_.push_back(c);
 	}

 	virtual void deregister_mbuffer(buffer_data bdata) override
 	{
 		auto it = buffers_.begin();
 		auto pointee = *it;

 		while(pointee->data->buffer_id != bdata.buffer_id && it != buffers_.end() ) 
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

 	buffer_data buffer_for_connection (const char* name)
 	{
 		buffer_data bdata(-1,name);

 		auto it = buffers_.begin();
 		auto buff = *it;

 		while(buff->data->buffer_name != bdata.buffer_name && it != buffers_.end() ) 
		{
			++it;
			buff = *it;
		}

		return *(buff->data);
 	}

 	tcp_session() { };

 	virtual void put_message_in(const char* msg, buffer_data* bdata) override
 	{
 		std::cout<<"begin put" << std::endl;
 		std::cout<<"buffer_data (id):" << bdata->buffer_id << std::endl;

 		auto it = buffers_.begin();
 		auto buff = *it;

 		while(buff->data->buffer_id != bdata->buffer_id && it != buffers_.end() ) 
		{
			std::cout<<"buff->data (id):" << buff->data->buffer_id << std::endl;

			++it;
			buff = *it;
		}
		std::cout<<"Finding buffer" << std::endl;

		if (it == buffers_.end())
			return;

		std::cout<< "Found buffer" << std::endl;

 		buff->buffer->in_msg_push(msg);

 		std::cout<<"Pushed msg" << std::endl;

 		session_data s;

 		s.name_ = this->name_;
 		s.buffer = buff->data;

 		std::cout<<"starting notify" << std::endl;

 		this->notify(IN, s);

 		std::cout<<"Notified" << std::endl;
 	}

	virtual void put_message_out(const char* msg, buffer_data* bdata) override
 	{
 		auto it = buffers_.begin();
 		auto buff = *it;

 		while(buff->data->buffer_id != bdata->buffer_id && it != buffers_.end() ) 
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


 	const char* get_message_in(buffer_data* bdata)
 	{
 		auto it = buffers_.begin();
 		auto buff = *it;

 		while(buff->data->buffer_id != bdata->buffer_id && it != buffers_.end() ) 
		{
			++it;
			buff = *it;
		}

		if (it == buffers_.end())
			return "";

		return buff->buffer->in_msg_get();

 	}

 	const char* get_message_out(buffer_data* bdata)
 	{
 		auto it = buffers_.begin();
 		auto buff = *it;

 		while(buff->data->buffer_id != bdata->buffer_id && it != buffers_.end() ) 
		{
			++it;
			buff = *it;
		}

		if (it == buffers_.end())
			return "";

		return buff->buffer->out_msg_get();
 	}

 	virtual buffer_data* get_free_bdata()
 	{

 		auto it = buffers_.begin();
 		auto buff = *it;

 		std::cout << "Getting next free buffer" << std::endl;

 		while(!buff->free_buff && it != buffers_.end() ) 
		{
			++it;
			buff = *it;
		}

		if (it == buffers_.end())
			return nullptr;

		std::cout << "GOT it.. it Ain't nullptr" << std::endl;

		std::cout << buff->data->buffer_id << std::endl;


		buff->free_buff = false;

		return buff->data;
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