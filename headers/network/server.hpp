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
#include <memory>
#include <utility>
#include <boost/asio.hpp>

#include "connection.hpp"

using boost::asio::ip::tcp;

 namespace network
 {

  typedef void (*conn_callback) (std::shared_ptr<tcp_connection>);

	class server
	{
	public:
		server();
		~server();
	};


 	class tcp_server
 	{
    tcp::acceptor acceptor_;
    tcp::socket socket_; 
    conn_callback conn_callback_;

    
    void do_accept()
    {
      acceptor_.async_accept(socket_,
          [this](boost::system::error_code ec)
          {
            if (!ec)
            {
              auto new_conn = std::make_shared<tcp_connection>(std::move(socket_));

              conn_callback_(new_conn);

              new_conn->start();
            }
            do_accept();
          });
    }

 	public:
 		tcp_server(boost::asio::io_service& io_service, short port,  conn_callback cnn_clbk)
    : acceptor_(io_service, tcp::endpoint(tcp::v4(), port)),
      socket_(io_service),
      conn_callback_(cnn_clbk)
		{
			do_accept();
		}

 		virtual ~tcp_server() {};
 	};


 }

 #endif /* NETWORK_SERVER_ */