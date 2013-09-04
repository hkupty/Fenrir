/*
 * select_test.cpp
 *
 *  Created on: 28 Aug 2013
 *      Author: Henry J Kupty
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include <sys/time.h>
 #include <sys/types.h>
 #include <unistd.h>

 int main(int argc, char* argv[])
 {
 	fd_set rfds;
 	struct timeval tv;
 	int retval;

 	FD_ZERO(&rfds);
 	FD_SET(0, &rfds);

 	tv.tv_sec = 5;
 	tv.tv_usec = 0;

 	retval = select(1, &rfds, NULL, NULL, &tv);

 	if (retval == -1)
 	{
 		perror("select()");
 	}
 	else if (retval)
 	{
 		printf("Data is available now!\n");
 	}
 	else
 	{
 		printf("No data within 5 secs.\n");
 	}

 	exit(EXIT_SUCCESS);
 }