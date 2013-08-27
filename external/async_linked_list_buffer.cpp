/*
 * async_linked_list_buffer.cpp
 *
 *  Created on: 12 Aug 2013
 *      Author: Henry J Kupty
 */

#include "../headers/message_buffer.hpp"
#include "../headers/message.hpp"

namespace buffers
{

template<class T>
class container
{
	public:
	T 				current_;
	container<T>*	next_;

	container<T>(T _curr) : current_(_curr) {};
};

template<class T>
class llist
{
	container<T>* first_node_;
	container<T>* last_node_;

	int llist_size;
	int llist_max_size;

	public:

		llist(int max) : first_node_(nullptr), last_node_(nullptr), llist_size(0), llist_max_size(max) {}
		llist() : first_node_(nullptr), last_node_(nullptr), llist_size(0), llist_max_size(1024) {}
		~llist()
		{
			while(llist_size > 0)
				this->get();
		}

		bool push (T value)
		{
			std::cout << "Pushing .." << std::endl;

			if (this->llist_size == this->llist_max_size)
				return false;

			container<T>* c = new container<T>(value);

			if (this->first_node_ == nullptr)
			{
				this->first_node_ = c;
			}
			else 
			{
				this->last_node_->next_ = c;
			}

			std::cout << "Updating pointers.." << std::endl;

			this->last_node_ = c;
			this->last_node_->next_ = nullptr;

			this->llist_size++;

			std::cout << "Done!" << std::endl;

			return true;
		}

		T get ()
		{
			if (this->first_node_ == nullptr)
				return NULL;

			container<T>* item = this->first_node_;
			
			this->first_node_ = item->next_;

			this->llist_size--;

			T value = item->current_;

			delete item;

			return value;
		}
};


class async_linked_list_buffer : public message_buffer
 {
 protected:
 	llist<const char*> in_llist_;
 	llist<const char*> out_llist_;

 	int in_qtd_ = 0;
 	int out_qtd_ = 0;

 public:

 	virtual bool in_msg_push(const char* _msg) override
 	{
 		std::cout << "Starting push" << std::endl;
 		return in_llist_.push(_msg);
 	}

 	virtual bool out_msg_push(const char* _msg) override
 	{
 		return out_llist_.push(_msg);
 	}

 	virtual const char* in_msg_get()
 	{
 		return in_llist_.get();
 	}

 	virtual const char* out_msg_get()
 	{
 		return out_llist_.get();
 	}

 	virtual ~async_linked_list_buffer() override
 	{
 		delete &in_llist_;
 		delete &out_llist_;
 	}

 };
}

buffers::message_buffer* create_async_ll_buff()
{
	return new buffers::async_linked_list_buffer;
}

void delete_async_ll_buff(buffers::message_buffer* ref)
{
	delete ref;
}

#ifndef API_
#define API_

external::API<buffers::message_buffer> api_table = {create_async_ll_buff, delete_async_ll_buff};

#endif /* API_*/ 