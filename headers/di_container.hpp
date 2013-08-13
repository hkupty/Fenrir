/*
 * di_container.hpp
 *
 *  Created on: 12 Jun 2013
 *      Author: Henry J Kupty
 */

#ifndef DI_CONTAINER_HPP_
#define DI_CONTAINER_HPP_

#include<boost/unordered_map.hpp>

template < class _T, class _api >
class di_container
{
	typedef boost::unordered_map<_T*,std::string> name_t;
	typedef boost::unordered_map<std::string, int> counter_t;
	typedef boost::unordered_map<std::string, void*> handler_t;
	typedef boost::unordered_map<std::string, _api*> api_t;

	typedef typename name_t::iterator name_it;
	typedef counter_t::iterator counter_it;
	typedef handler_t::iterator handler_it;
	typedef typename api_t::iterator api_it;

protected:
	api_t api_pointers;
	handler_t handler_api;
	counter_t inst_count;
	name_t name_pointer;

public:
	virtual _T* create_t(std::string);
	virtual void destroy_t(_T*);
	virtual ~di_container();
};



#endif /* DI_CONTAINER_HPP_ */
