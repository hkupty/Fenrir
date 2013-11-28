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

 	~tcp_session() override
 	{
 		for (std::vector<buffer_container*>::iterator i = buffers_.begin(); i != buffers_.end(); ++i) 
		{
			delete *i;
		}
 	}

 	virtual void register_mbuffer(buffers::message_buffer* buffer, const char* buff_name) override
 	{
		++mbuffer_qtd_;

 		buffer_data* d = new buffer_data(mbuffer_inc_,buff_name);

 		buffer_container* c = new buffer_container(d, buffer);

 		this->buffers_.push_back(c);
 	}

 	virtual void deregister_mbuffer(buffer_data bdata) override
 	{
 		auto it = buffers_.begin();

 		while((*it)->data->buffer_id != bdata.buffer_id && it != buffers_.end())  ++it;

 		if (it == buffers_.end())
			return;

		this->buffers_.erase(it);
		this->mbuffer_qtd_--;

		delete (*it);
 	}

 	virtual void start_session()
 	{

 	}

 	buffer_data buffer_for_connection (const char* name)
 	{
 		buffer_data bdata(-1,name);

 		auto it = buffers_.begin();

 		while((*it)->data->buffer_name != bdata.buffer_name && it != buffers_.end()) ++it;

 		if (it == buffers_.end())
			return bdata;

		return *((*it)->data);
 	}

 	tcp_session() { };

 	virtual void put_message_in(msg_t msg, buffer_data* bdata) override
 	{
 		if (bdata->buffer_id == -1)
 		{
 			
 			return;
 		}

 		auto it = buffers_.begin();

 		while((*it)->data->buffer_id != bdata->buffer_id && it != buffers_.end() ) ++it;


		if (it == buffers_.end())
			return;

 		if ((*it)->buffer->in_msg_push(msg))
		{
	 		session_data s;

	 		s.name_ = this->name_;
	 		s.buffer = (*it)->data;

	 		this->notify(IN, s);
	 	}
 	}

	virtual void put_message_out(msg_t msg, buffer_data* bdata) override
 	{
 		auto it = buffers_.begin();

 		while((*it)->data->buffer_id != bdata->buffer_id && it != buffers_.end() ) ++it;

		if (it == buffers_.end())
			return;

 		(*it)->buffer->out_msg_push(msg);

 		session_data s;

 		s.name_ = this->name_;
 		s.buffer = (*it)->data;

 		this->notify(OUT, s);
 	}


 	msg_t get_message_in(buffer_data* bdata)
 	{
 		auto it = buffers_.begin();

 		while((*it)->data->buffer_id != bdata->buffer_id && it != buffers_.end()) ++it;

		// if (it == buffers_.end())
		// 	return "";

		return (*it)->buffer->in_msg_get();

 	}

 	msg_t get_message_out(buffer_data* bdata)
 	{
 		auto it = buffers_.begin();

 		while((*it)->data->buffer_id != bdata->buffer_id && it != buffers_.end()) ++it;

		// if (it == buffers_.end())
		// 	return "";


		return (*it)->buffer->out_msg_get();
 	}

 	virtual buffer_data* get_free_bdata()
 	{

 		auto it = buffers_.begin();

 		while(!(*it)->free_buff && it != buffers_.end() ) ++it;

		if (it == buffers_.end())
		{
			buffer_data bdata(-1,"");
			return &bdata;
		}

		(*it)->free_buff = false;

		return (*it)->data;
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