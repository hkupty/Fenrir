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
	 class connection : public std::enable_shared_from_this<connection>
	 {

	 protected:
	 	std::function<bool(const char*)> in_msg_callback_;
	 	std::function<const char*()> out_msg_callback_;
	 	enum { max_length = 1024 };
	    char* in_data_ = new char[max_length];
	    const char* out_data_ = new char[max_length];

	 public:
	 	connection() {};
	 	virtual ~connection() {};

	 	void in_msg_callback_rg(std::function<bool(const char*)> _callback)
	    {
	    	this->in_msg_callback_ = _callback;
	    }

	    void out_msg_callback_rg(std::function<const char*()> _callback)
	    {
	    	this->out_msg_callback_ = _callback;
	    }

	 };

	class tcp_connection : public connection
	{
	
	private:
		tcp::socket socket_;

		void do_read()
		{
			auto self(shared_from_this());
			socket_.async_read_some(boost::asio::buffer(in_data_, max_length),
			    [this, self](boost::system::error_code ec, std::size_t length)
			    {
			      if (!ec)
			      {
			        in_msg_callback_(in_data_);
			        in_data_ = new char[max_length];
			      }

			      out_data_ = out_msg_callback_();
			      do_write();
			      
			    });
		}

		void do_write()
		{
			auto self(shared_from_this());
			boost::asio::async_write(socket_, boost::asio::buffer(out_data_, sizeof(out_data_)),
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

	 	virtual ~tcp_connection() {};
	 };
}

 #endif /* NETWORK_CONNECTION_*/