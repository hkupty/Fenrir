/*
 * server.hpp
 *
 *  Created on: 15 Aug 2013
 *      Author: Henry J Kupty
 */

 #ifndef NETWORK_SERVER_
 #define NETWORK_SERVER_


#include <cstdlib>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>

#include "connection.hpp"

using boost::asio::ip::tcp;

 namespace network
 {

  typedef void (*conn_callback) (connection*);

	class server
	{
	public:
		server();
		~server();
	};


 	class tcp_server
 	{
    boost::asio::io_service& io_service_;
    tcp::acceptor acceptor_;
    conn_callback conn_callback_;

    
    void start_accept()
    {
      network::tcp_connection* new_session = new network::tcp_connection(io_service_);

      acceptor_.async_accept(new_session->socket(),
          boost::bind(&tcp_server::handle_accept, this, new_session,
            boost::asio::placeholders::error));
    }

    void handle_accept(network::tcp_connection* new_session,
        const boost::system::error_code& error)
    {
      if (!error)
      {
        conn_callback_(new_session);
        new_session->start();
      }
      else
      {
        delete new_session;
      }

      start_accept();
    }

 	public:
 		tcp_server(boost::asio::io_service& io_service, short port, conn_callback cnn_clbk)
 		: io_service_(io_service),
	    acceptor_(io_service, tcp::endpoint(tcp::v4(), port)),
      conn_callback_(cnn_clbk)
		{
			start_accept();
		}

 		virtual ~tcp_server() {};
 	};


 }

 #endif /* NETWORK_SERVER_ */