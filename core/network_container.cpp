/*
 * network_container.cpp
 *
 *  Created on: 26 Aug 2013
 *      Author: Henry J Kupty
 */

 #include "../headers/network_container.hpp"

 bool network_container::request_tcp_port(int port)
 {
 	int sockfd , newsockfd, clilen, n;

 	struct sockaddr_in serv_addr;


 	sockfd = socket(AF_INET, SOCK_STREAM, 0);

 	if (sockfd < 0)
 	{
 		std::cout << "ERROR opening socket" << std::endl;
 		return false;
 	}

 	this->sockets.push_back(sockfd);

 	bzero((char*)(&serv_addr), sizeof(serv_addr));

 	serv_addr.sin_family 	  = AF_INET;
 	serv_addr.sin_port   	  = htons(port);
 	serv_addr.sin_addr.s_addr = INADDR_ANY;

 	if (bind(sockfd, (struct sockaddr *)(&serv_addr), sizeof(serv_addr)) < 0)
	{
		std::cout << "ERROR opening socket" << std::endl;
		return false;
	}
	
	listen(sockfd,5);



 }