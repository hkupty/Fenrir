/*
 * infra_tester.cpp
 *
 *  Created on: 15 Aug 2013
 *      Author: Henry J Kupty
 */

#include "external/async_linked_list_buffer.cpp"
#include "external/tcp_session.cpp"
#include "headers/observable.hpp"
#include "headers/session.hpp"

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

		s1->register_mbuffer(asbuff_1,"b1");
		s1->register_mbuffer(asbuff_2,"b2");
		s2->register_mbuffer(asbuff_3,"b3");
		s2->register_mbuffer(asbuff_4,"b4");

		std::cout << "Starting" << std::endl;

		std::cout << "Done!" << std::endl;

	}
	catch (std::exception& e)
	{
		std::cout << "Error..." << std::endl;
	}
 	
 	return 0;
 }