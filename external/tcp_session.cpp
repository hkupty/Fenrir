/*
 * tcp_session.cpp
 *
 *  Created on: 12 Aug 2013
 *      Author: Henry J Kupty
 */

 #include "../headers/session.hpp"
 #include "../headers/external.hpp"

 #include <boost/container/list.hpp>
 #include <functional>

namespace sessions
{
 class tcp_session : public session
 {
 	int curr_buffer_;

 	/*
 	void connection_callback (std::shared_ptr<network::tcp_connection> conn)
 	{
 		auto it = buffers.begin();

 		//TODO: Implement intelligent logic for buffer selection
 		buffers::message_buffer* nx = *( std::next(it, curr_buffer_) );

 		auto in_msg_callback = std::bind(&buffers::message_buffer::in_msg_push, nx, std::placeholders::_1);

 		conn->in_msg_callback_rg(in_msg_callback);
 	}
 	*/

 protected:
 	boost::container::list<buffers::message_buffer*> buffers;

 public:
 	virtual void register_mbuffer(buffers::message_buffer* buffer) override
 	{
 		this->buffers.push_back(buffer);
 		this->mbuffer_qtd_++;
 	}

 	virtual void deregister_mbuffer(buffers::message_buffer* buffer) override
 	{
		this->buffers.remove(buffer);
		this->mbuffer_qtd_--;
 	}

 	virtual void start_session()
 	{

 	}

 	tcp_session() : curr_buffer_(0) { };

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