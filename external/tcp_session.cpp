/*
 * tcp_session.cpp
 *
 *  Created on: 12 Aug 2013
 *      Author: Henry J Kupty
 */


 #include "../headers/session.hpp"
 #include "../headers/external.hpp"

 #include <boost/container/list.hpp>


#include <cstdlib>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

 class tcp_session : public sessions::session
 {
tcp::acceptor* acceptor_;

int port_;
short curr_buffer;

 protected:
 	boost::container::list<buffers::message_buffer*> buffers;

 	void handle_accept(const boost::system::error_code& error)
 	{
 		if(!error)
 		{
 			if (_session_mbuffer_qtd > curr_buffer)
 			{
 				auto it = this->buffers.begin();
 				it = std::next(it, curr_buffer++);
 			}

 			start_async();
 		}
 	}

 	void start_async()
 	{
 		acceptor_->async_accept(io_,
 			boost::bind(&tcp_session::handle_accept, this, boost::asio::placeholders::error));
 	}

 public:
 	virtual void register_mbuffer(buffers::message_buffer* buffer) override
 	{
 		this->buffers.push_back(buffer);
 	}

 	virtual void deregister_mbuffer(buffers::message_buffer* buffer) override
 	{
		this->buffers.remove(buffer);
 	}


 	virtual void start_session(boost::asio::io_service& io, int port)
 	{
 		acceptor_ = new tcp::acceptor(io, tcp::endpoint(tcp::v4(), port));
 		
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

