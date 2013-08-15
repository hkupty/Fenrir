/* buffer_tester.cpp
 *
 *  Created on: 14 Jun 2013
 *      Author: Henry J Kupty
 * Description: Dynamically creates, manipulates and deletes test objects according to argv[1] parameter,
 *              validating each message_buffer implementation's health.
 */

 #import "headers/message_buffer.hpp"
 #import "headers/external.hpp"

 #include <dlfcn.h>
 #include <unistd.h>

 int main(int argc, char const *argv[])
 {

 	if(argc != 2)
 	{
 		std::cout << "Invalid arg.." << std::endl;
 		return 1;
 	}

 	const char* impl = argv[1];

 	void* dependency_handlr = dlopen(impl, RTLD_LAZY);

 	if(!dependency_handlr)
	{
		std::cout << "\033[31mERR @ dlopen(): " <<  dlerror() << "\033[0m" << std::endl;
		return 1;		
	}
	else
		std::cout << "\033[32mOK @ dlopen(): Opened ok!" << "\033[0m" << std::endl;

	external::API<buffers::message_buffer>* load = static_cast<external::API<buffers::message_buffer>*>(dlsym(dependency_handlr, "api_table"));

	if (!load) 
	{
		std::cout << "\033[31mERR @ dlsym(): " <<  dlerror() << "\033[0m" << std::endl;
		return 1;		
	}else
		std::cout << "\033[32mOK @ dlsym(): Loaded API correctly!" << "\033[0m" << std::endl;

	buffers::message_buffer* mbuffer = load->create();

	load->destroy(mbuffer);
 	
 	return 0;
 }

