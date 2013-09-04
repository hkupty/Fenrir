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
 class observable
 {

 protected:
 	 observable() {};
 	~observable() {};
 	
 	void notify_(const T &message, const std::vector<observer<T>> &observers)
	{
		for(auto it = observers.begin(); it != observers.end(); ++it)
		{
			auto pointee = *it;
			pointee.update(message);
		}
 	}

 	void attach_(const std::vector<observer<T>> &observers, observer<T> &new_obs)
 	{
 		observers.push_back(new_obs);
 	}

 };
 
 
 template<class T>
 class single_channel_observable : protected observable<T>
 {
private:
 	std::vector<observer<T>> observers_;

 protected:
 	 single_channel_observable() {};
 	~single_channel_observable() {};
 	virtual void set_channel();

 	void notify(T &message)
 	{
 		this->notify_(message, observers_);
 	}

 	void attach(const observer<T> &observer)
 	{
 		this->attach_(observers_, observer);
 	}

 };

template<class T>
 class multi_channel_observable : protected observable<T>
 {

 private:
 	boost::unordered_map<CHANNEL,std::vector<observer<T>>* > observers_;

 protected:
  	 multi_channel_observable() 
  	 {
  	 	observers_[IN]   = new std::vector<observer<T>>;
  	 	observers_[OUT]  = new std::vector<observer<T>>;
  	 };
 	~multi_channel_observable() {};

	void notify(CHANNEL c, T &message)
	{
		auto v = observers_[c];
		this->notify_(message, v);
	}

	void attach(CHANNEL c, const observer<T> &observer)
 	{
 		this->attach_(observers_[c], observer);
 	}
 };
 
 #endif /* OBSERVABLE_HPP_*/