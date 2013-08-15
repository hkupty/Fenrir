/*
 * tcp_session.cpp
 *
 *  Created on: 12 Aug 2013
 *      Author: Henry J Kupty
 */


 #include "../headers/session.hpp"
 #include "../headers/external.hpp"

 #include <boost/container/list.hpp>

 class tcp_session : public sessions::session
 {

 protected:
 	boost::container::list<buffers::message_buffer*> buffers;

 public:
 	virtual void register_mbuffer(buffers::message_buffer* buffer) override
 	{
 		this->buffers.push_back(buffer);
 	}

 	virtual void deregister_mbuffer(buffers::message_buffer* buffer) override
 	{
		this->buffers.remove(buffer);
 	}


 	tcp_session() : curr_buffer(0) {};

 };

 sessions::session* create_tcp()
 {
 	return new tcp_session;
 }

 void destroy_tcp(sessions::session* ref)
 {
 	delete ref;
 }

 external::API<sessions::session> api_table = {create_tcp, destroy_tcp};

