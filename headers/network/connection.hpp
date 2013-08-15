/*
 * connection.hpp
 *
 *  Created on: 15 Aug 2013
 *      Author: Henry J Kupty
 */

 #ifndef NETWORK_CONNECTION_
 #define NETWORK_CONNECTION_

using boost::asio::ip::tcp;

namespace network
{
	typedef bool (*put_message) (const char*);
	 
	 class connection
	 {
	 protected:
	 	put_message callback_;
	 	enum { max_length = 1024 };
	    char data_[max_length];
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

		void handle_read(const boost::system::error_code& error,
	      size_t bytes_transferred)
		{
			if (!error)
			{
			  this->callback_(data_);
			  clear(data_);
			  start();
			}
			else
			{
			  delete this;
			}
		}
		void clear(char* arr)
		{
			for (int i = 0; i < max_length; i++)
				arr[i] = '\0';
		}

	 public:
	 	tcp_connection(boost::asio::io_service& io_service)
	    : socket_(io_service) {}

	    tcp::socket& socket()
		{
			return socket_;
		}

		void start()
		{
			socket_.async_read_some
			(boost::asio::buffer(data_, max_length),
		    	boost::bind(&tcp_connection::handle_read, this,
		    		boost::asio::placeholders::error,
		    		boost::asio::placeholders::bytes_transferred));
		}

	 	virtual ~tcp_connection() {};
	 
	 	/* data */
	 };
}

 #endif /* NETWORK_CONNECTION_*/