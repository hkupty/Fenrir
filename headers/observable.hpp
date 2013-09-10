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
 	
 	void notify_(T message, std::vector<observer<T>> observers)
	{
		typename std::vector<observer<T>>::iterator it;

		for(it = observers.begin(); it != observers.end(); ++it)
		{
			it->update(message);
		}
 	}

 	void attach_(std::vector<observer<T>> observers, observer<T> new_obs)
 	{
 		observers.push_back(new_obs);
 	}

 };
 
 
 template<class T>
 class single_channel_observable : protected observable<T>
 {
private:
 	std::vector<observer<T>> observers_;

 public:
 	 single_channel_observable() {};
 	~single_channel_observable() {};
 	virtual void set_channel();

 	void notify(T &message)
 	{
 		this->notify_(message, observers_);
 	}

 	void attach(observer<T> observer)
 	{
 		this->attach_(observers_, observer);
 	}

 };

template<class T>
 class multi_channel_observable : protected observable<T>
 {

 private:
 	boost::unordered_map<CHANNEL,std::vector<observer<T>>*> observers_;

 public:
  	 multi_channel_observable() 
  	 {
  	 	observers_[IN]   = new std::vector<observer<T>>;
  	 	observers_[OUT]  = new std::vector<observer<T>>;
  	 };
 	~multi_channel_observable() {};

	void notify(CHANNEL c, T message)
	{
		auto obs_vect = *observers_[c];
		this->notify_(message, obs_vect);
	}

	void attach(CHANNEL c, observer<T> &observer)
 	{
 		auto obs_vect = *observers_[c];
 		this->attach_(obs_vect, observer);
 	}
 };
 
 #endif /* OBSERVABLE_HPP_*/