/*
 * tcp_session.cpp
 *
 *  Created on: 12 Aug 2013
 *      Author: Henry J Kupty
 */


 #include "../headers/session.hpp"
 #include "../headers/external.hpp"
 #include "../headers/network/server.hpp"

 #include <boost/container/list.hpp>

 class tcp_session : public sessions::session
 {
 	network::tcp_server* t_serv;
 	int curr_buffer;

 	void register_buffer (std::shared_ptr<network::tcp_connection> conn)
 	{

 		auto it = buffers.begin();
 		auto nx = std::next(it, curr_buffer);
 		conn->register_callback(nx.push_message);
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
 		t_serv = new network::tcp_server(io, port, this->register_mbuffer);
 	}

 	tcp_session() : curr_buffer(0) { };

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

