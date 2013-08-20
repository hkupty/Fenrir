/*
 * tcp_session.cpp
 *
 *  Created on: 12 Aug 2013
 *      Author: Henry J Kupty
 */

 #include "../headers/session.hpp"
 #include "../headers/external.hpp"
 #include "../headers/network/server.hpp"
 #include "../headers/network/connection.hpp"

 #include <boost/container/list.hpp>
 #include <functional>

 class tcp_session : public sessions::session
 {
 	network::tcp_server* t_serv;

 	int curr_buffer;

 	void connection_callback (std::shared_ptr<network::tcp_connection> conn)
 	{

 		auto it = buffers.begin();

 		//TODO: Implement intelligent logic for buffer selection
 		buffers::message_buffer* nx = *( std::next(it, curr_buffer) );

 		auto in_msg_callback = std::bind(&buffers::message_buffer::in_msg_push, nx, std::placeholders::_1);
 		auto out_msg_callback = std::bind(&buffers::message_buffer::out_msg_get, nx);

 		conn->in_msg_callback_rg(in_msg_callback);
 		conn->out_msg_callback_rg(out_msg_callback);
 	}

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

 	virtual void start_session(boost::asio::io_service& io, int port)
 	{
 		this->t_serv = new network::tcp_server(io, port);

 		this->t_serv->connection_callback_rg(std::bind(&tcp_session::connection_callback, this, std::placeholders::_1));

 		this->t_serv->start();
 	}

 	tcp_session() : curr_buffer(0) { };

 	virtual ~tcp_session() override
 	{
 		delete t_serv;
 	}

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

