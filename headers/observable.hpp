/*
 * observable.hpp
 *
 *  Created on: 03 Sep 2013
 *      Author: Henry J Kupty
 */

 #ifndef OBSERVABLE_HPP_
 #define OBSERVABLE_HPP_

 #include "observer.hpp"
 #include <vector>
 #include <boost/unordered_map.hpp>

 enum CHANNEL { IN, OUT };
 
 template<class T>
 class single_channel_observable
 {

private:
 	std::vector<observer<T>> observers_;

 public:
 	single_channel_observable(CHANNEL);
 	~single_channel_observable();

 	void notify()
 	{
 		for(auto i = observers_.begin(); i != observers_.end(); ++i)
 			i.update(static_cast<T>(this));
 	}
 };

template<class T>
 class multi_channel_observable
 {

 private:
 	boost::unordered_map<CHANNEL,std::vector<observer<T>>> observers_;

 public:
 	multi_channel_observable();
 	~multi_channel_observable();

	void notify(CHANNEL c)
	{
		auto v = observers_[c];
		for (auto i = v.begin(); i != v.end(); ++i)
			i.update(static_cast<T>(this));
	}

 	
 };
 
 #endif /* OBSERVABLE_HPP_*/