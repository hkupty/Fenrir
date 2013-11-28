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
 	
 	void notify_(const T &message, std::vector<observer<T>*> &observers)
	{
		typename std::vector<observer<T>*>::const_iterator it;

		for(it = observers.begin(); it != observers.end(); ++it)
		{
			auto pointee = *it;
			pointee->update(message);
		}

		std::cout << "UPDATE DONE" << std::endl;
 	}

 };
 
 
 template<class T>
 class single_channel_observable : protected observable<T>
 {
private:
 	std::vector<observer<T>*> observers_;

 public:
 	 single_channel_observable() {};
 	~single_channel_observable() { delete observers_; };
 	virtual void set_channel();

 	void notify(const T &message)
 	{
 		this->notify_(message, observers_);
 	}

 	void attach(observer<T>* &observer)
 	{
 		this->observers_.push_back(observer);
 	}

 };

template<class T>
 class multi_channel_observable : protected observable<T>
 {

 private:
 	boost::unordered_map<CHANNEL,std::vector<observer<T>*>*> observers_;

 public:
  	 multi_channel_observable() 
  	 {
  	 	observers_[IN]   = new std::vector<observer<T>*>;
  	 	observers_[OUT]  = new std::vector<observer<T>*>;
  	 };

 	~multi_channel_observable() 
 	{
 		typename std::vector<observer<T>*>::iterator it;

 		for (it = observers_[IN]->begin(); it != observers_[IN]->end(); ++it)	delete (*it);
 		for (it = observers_[OUT]->begin(); it != observers_[OUT]->end(); ++it) delete (*it);

 		delete observers_[IN];
 		delete observers_[OUT];
 	};

	void notify(const CHANNEL &c, const T &message)
	{
		auto obs_vect = *observers_[c];
		this->notify_(message, obs_vect);
	}

	void attach(const CHANNEL &c, observer<T>* observer)
 	{
 		observers_[c]->push_back(observer);
 	}
 };
 
 #endif /* OBSERVABLE_HPP_*/