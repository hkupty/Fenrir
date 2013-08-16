/*
 * connection.hpp
 *
 *  Created on: 15 Aug 2013
 *      Author: Henry J Kupty
 */

 #ifndef NETWORK_CONNECTION_
 #define NETWORK_CONNECTION_

#include <cstdlib>
#include <iostream>
#include <memory>
#include <utility>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

namespace network
{
	typedef bool (*put_message) (const char*);
	 
	 class connection : public std::enable_shared_from_this<connection>
	 {

	 protected:
	 	put_message callback_;
	 	enum { max_length = 1024 };
	    char* data_ = new char[max_length];

	 public:
	 	connection() {};
	 	virtual ~connection() {};

	 	void register_callback(put_message _callback)
	    {
	    	this->callback_ = _callback;
	    }

	 };

	class tcp_connection : public connection
	{
	
	private:
		tcp::socket socket_;

		void do_read()
		{
			auto self(shared_from_this());
			socket_.async_read_some(boost::asio::buffer(data_, max_length),
			    [this, self](boost::system::error_code ec, std::size_t length)
			    {
			      if (!ec)
			      {
			        callback_(data_);
			        data_ = new char[max_length];
			      }
			      do_read();
			    });
		}

		void do_write()
		{
			auto self(shared_from_this());
			boost::asio::async_write(socket_, boost::asio::buffer(data_, sizeof(data_)),
			    [this, self](boost::system::error_code ec, std::size_t /*length*/)
			    {
			      if (!ec)
			      {
			      	do_read();
			      }

			    });
		}

	public:
	 	tcp_connection(tcp::socket socket) : socket_(std::move(socket)) {}

		void start()
		{
			do_read();
		}

		
		void post_message(char* _msg)
		{
			data_ = _msg;
			do_write();
		}

	 	virtual ~tcp_connection() {};
	 };
}

 #endif /* NETWORK_CONNECTION_*/