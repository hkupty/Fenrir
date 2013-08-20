/*
 * infra_tester.cpp
 *
 *  Created on: 15 Aug 2013
 *      Author: Henry J Kupty
 */

#include "headers/network/server.hpp"
#include "headers/network/connection.hpp"
#include <stdio.h>

bool in_msg(const char* msg)
{
	std::cout << "in: " << msg << std::endl;
	return true;
}

const char* out_msg()
{
	return "Teste\n\0"  ;
}

void msg_mnp(std::shared_ptr<network::tcp_connection> _conn)
{
	_conn->in_msg_callback_rg(in_msg);
	_conn->out_msg_callback_rg(out_msg);
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

		network::tcp_server s(io_service, atoi(argv[1]));

		s.connection_callback_rg(std::bind(msg_mnp, std::placeholders::_1));

		s.start();

		io_service.run();

	}
	catch (std::exception& e)
	{
		std::cout << "Error..." << std::endl;
	}
 	
 	return 0;
 }