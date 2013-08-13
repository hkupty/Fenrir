/*
 * run.cpp
 *
 *  Created on: 11 Jun 2013
 *      Author: Henry J Kupty
 */

#include "../headers/default_config.hpp"
#include "../headers/exec_environment.hpp"
#include "../headers/log.hpp" 

#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <iostream>
#include <fstream>

const std::string k_daem = std::string(_log::_bold + "[DAEMON    ]" + _log::_clr);

int main(){
	/*
	 * TODO:
	 * DBUS.
	 */

	pid_t pid, sid;

	pid = fork();

	if (pid < 0) exit(EXIT_FAILURE);
	if (pid > 0) exit(EXIT_SUCCESS);

	sid = setsid();

	if (sid < 0) exit(EXIT_FAILURE);

	// if ((chdir("/")) < 0) exit(EXIT_FAILURE);

	umask(0);

	if (pid_t pid = fork())
    {
      if (pid > 0) exit(EXIT_SUCCESS);
      else         exit(EXIT_FAILURE);
    }

	close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    const char* output = "/var/log/Fenrir.log";

    std::ofstream out(output);

    std::cout.rdbuf(out.rdbuf());

    std::cout << _log::_scc <<  k_daem << "START" << std::endl;

	exec::exec_environment env;
	env.start();

	//while(1) { sleep(50); }

	std::cout << _log::_scc <<  k_daem << "STOP" << std::endl;

	delete &env;

	std::cout << _log::_scc <<  k_daem << "DONE, QUIT" << std::endl;

	std::cout.flush();

	close(STDOUT_FILENO);

	exit(EXIT_SUCCESS);
}


