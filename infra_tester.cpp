/*
 * infra_tester.cpp
 *
 *  Created on: 15 Aug 2013
 *      Author: Henry J Kupty
 */

#include "external/async_linked_list_buffer.cpp"
#include "external/tcp_session.cpp"

#include <stdio.h>

 int main(int argc, char const *argv[])
 {
	try
	{
		if (argc != 3)
		{
			std::cerr << "Usage: infra_tester <port1> <port2>\n\0";
			return 1;
		}

		boost::asio::io_service io_service;

		using namespace std;

		std::cout << "Preparing" << std::endl;

		sessions::session* s1 = new sessions::tcp_session;
		sessions::session* s2 = new sessions::tcp_session;

		buffers::message_buffer* asbuff_1 = new buffers::async_linked_list_buffer;
		buffers::message_buffer* asbuff_2 = new buffers::async_linked_list_buffer;
		buffers::message_buffer* asbuff_3 = new buffers::async_linked_list_buffer;
		buffers::message_buffer* asbuff_4 = new buffers::async_linked_list_buffer;

		std::cout << "Registering" << std::endl;

		s1->set_name(std::string("S_1"));
		s2->set_name(std::string("S_2"));

		s1->register_mbuffer(asbuff_1);
		s1->register_mbuffer(asbuff_2);
		s2->register_mbuffer(asbuff_3);
		s2->register_mbuffer(asbuff_4);

		std::cout << "Starting" << std::endl;

		s1->start_session(io_service, atoi(argv[1]));
		s2->start_session(io_service, atoi(argv[2]));

		std::cout << "Done!" << std::endl;

		io_service.run();

	}
	catch (std::exception& e)
	{
		std::cout << "Error..." << std::endl;
	}
 	
 	return 0;
 }