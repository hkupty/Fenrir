/*
 * mirror_boost_asio_sample.cpp
 *
 *  Created on: 15 Aug 2013
 *      Author: Henry J Kupty
 */

#include "headers/network/server.hpp"
#include "headers/network/connection.hpp"
#include <stdio.h>

bool print_msg(const char* msg)
{
	std::cout << msg << std::endl;
	return true;
}

void manipulate(network::connection* _conn)
{
	_conn->register_callback(print_msg);
}

 int main(int argc, char const *argv[])
 {
	try
	{
		if (argc != 2)
		{
			std::cerr << "Usage: async_tcp_echo_server <port>\n";
			return 1;
		}

		boost::asio::io_service io_service;

		using namespace std; // For atoi.

		network::tcp_server s(io_service, atoi(argv[1]), manipulate);

		io_service.run();
	}
	catch (std::exception& e)
	{
		std::cout << "Error..." << std::endl;
	}
 	
 	return 0;
 }