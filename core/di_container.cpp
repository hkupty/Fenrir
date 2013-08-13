/* di_container.cpp
 *
 *  Created on: 14 Jun 2013
 *      Author: Henry J Kupty
 */

#include "../headers/di_container.hpp"
#include "../headers/log.hpp"

#include <boost/unordered_map.hpp>
#include <dlfcn.h>
#include <unistd.h>

const std::string k_dic = std::string(_log::_bold + "[CONTAINER ]" + _log::_clr);

template < class _T, class _api >
_T* di_container< _T,_api >::create_t(std::string impl)
{
	_api* load = this->api_pointers[impl];

	if (!load)
	{
		std::cout << _log::_inf << k_dic <<  "LOADING NEW SHARED OBJECT" << std::endl;

		std::string filename =  "./" + impl + ".so";
		const char* _impl = filename.c_str();

		void* dependency_handlr = dlopen(_impl, RTLD_LAZY);

		if(!dependency_handlr)
		{
			std::cout << _log::_err << k_dic <<  dlerror() << std::endl;
			return NULL;		
		}

		load = (_api*) dlsym(dependency_handlr, "api_table");

		if (!load) 
		{
			std::cout << _log::_err << k_dic <<  dlerror() << std::endl;
			return NULL;		
		}

		this -> api_pointers[impl] = load;
		this -> handler_api[impl] = dependency_handlr;

		std::cout << _log::_scc << k_dic <<  "SHARED OBJECT LOADED SUCCESSFULLY" << std::endl;
	}

	_T* dependency = load->create();

	std::cout << _log::_scc << k_dic <<  "OBJECT CREATED SUCCESSFULLY" << std::endl;

	this -> inst_count[impl]++;
	this -> name_pointer[dependency] = impl;

	return dependency;
}

template < class _T, class _api >
void di_container< _T,_api >::destroy_t(_T* ref)
{
	std::cout << _log::_inf << k_dic <<  "UNLOADING OBJECT " << ref << std::endl;

	std::string impl = this->name_pointer[ref];

	this -> api_pointers[impl]->destroy(ref);
	this -> name_pointer.erase(ref);
	this -> inst_count[impl]--;

	std::cout << _log::_scc << k_dic <<  "OBJECT " << ref << " UNLOADED" << std::endl;

	if (this -> inst_count[impl] == 0)
	{
		std::cout << _log::_inf << k_dic <<  "UNLOADING SHARED OBJECT " << impl<< std::endl;
		
		int close = dlclose(this->handler_api[impl]);

		if (close != 0)
			std::cout << _log::_err << k_dic <<  "ERROR WHILE UNLOADING SHARED OBJECT " << impl << std::endl;	
		else
			std::cout << _log::_scc << k_dic <<  "UNLOADED SHARED OBJECT " << impl << " SUCCESSFULLY" << std::endl;

		this -> handler_api.erase(impl);
		this -> api_pointers.erase(impl);
		this -> inst_count.erase(impl);
	}
}

template < class _T, class _api >
di_container< _T,_api >::~di_container()
{
	std::cout << _log::_inf << k_dic <<  "OFFLOADING CONTAINER" << std::endl;

	if (!this->name_pointer.empty())
		for (name_it it = this->name_pointer.begin(); it != this->name_pointer.end(); ++it) this->destroy_t(static_cast<_T*>(it->first));

	std::cout << _log::_scc << k_dic <<  "CONTAINER OFFLOADED" << std::endl;
}


