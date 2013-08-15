/*
 * async_linked_list_buffer.cpp
 *
 *  Created on: 12 Aug 2013
 *      Author: Henry J Kupty
 */

#include "../headers/message_buffer.hpp"
#include "../headers/message.hpp"

 class async_linked_list_buffer : public buffers::message_buffer
 {

 	 template<class T>
	 class container
	 {

	 public:
	 	T 				_current;
	 	container<T>*	_next;

	 	container<T>(T curr_) : _current(curr_) {};
	 };

 protected:
 	container<message::msg*>* _last = NULL;
 	container<message::msg*>* _first = NULL;
 	int qtd_ = 0;

 public:
 	virtual bool push_message(message::msg* msg_) override
 	{
 		container<message::msg*>* c = new container<message::msg*>(msg_);

 		if ((this.qtd_ +1) > this.max_length_)
 			return false;

 		if (this->_last == NULL)
 		{
 			this->_last = c;
 			this->_first = this->_last;
 		}
 		else
 		{
 			this->_last->_next = c;
 			this->_last = c;
 		}
 		this->_last->_next = NULL;

 		return true;
 	}

 };

buffers::message_buffer* create_async_ll_buff()
{
	return new async_linked_list_buffer;
}

void delete_async_ll_buff(buffers::message_buffer* ref)
{
	delete ref;
}


 external::API<buffers::message_buffer> api_table = {create_async_ll_buff, delete_async_ll_buff};