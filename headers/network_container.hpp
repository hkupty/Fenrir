/*
 * network_container.hpp
 *
 *  Created on: 26 Aug 2013
 *      Author: Henry J Kupty
 */

 #ifndef NETWORK_CONTAINER_HPP_
 #define NETWORK_CONTAINER_HPP_

 #include <sys/types.h>
 #include <sys/socket.h>
 #include <netinet/in.h>
 #include <stdio.h>
 #include <stdlib.h>
 #include <boost/container/list.hpp>

 class network_container
 {

 	boost::container::list<int> sockets;
 	
 public:
 	network_container () {}
 	~network_container() {}

	/*
						  port
 	*/

	bool request_tcp_port(int);

 };
 
 #endif /* NETWORK_CONTAINER_HPP_*/	