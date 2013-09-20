/*
 * observer.hpp
 *
 *  Created on: 03 Sep 2013
 *      Author: Henry J Kupty
 */

 #ifndef OBSERVER_HPP_
 #define OBSERVER_HPP_
 
 template<class T>
 class observer
 {

 public:
 	observer(){};
 	~observer(){};

	virtual void update(T) const  = 0;
 	
 };
 
 #endif /* OBSERVER_HPP_*/