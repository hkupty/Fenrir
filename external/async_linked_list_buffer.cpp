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
	 	T 				current_;
	 	container<T>*	next_;

	 	container<T>(T _curr) : current_(_curr) {};
	 };

 protected:
 	container<const char*>* in_last_ = nullptr;
 	container<const char*>* in_first_ = nullptr;

 	container<const char*>* out_last_ = nullptr;
 	container<const char*>* out_first_ = nullptr;
 	
 	int in_qtd_ = 0;
 	int out_qtd_ = 0;

 public:

 	virtual bool in_msg_push(const char* msg_) override
 	{
 		container<const char*>* c = new container<const char*>(msg_);

 		if ((this.in_qtd_ + 1) > this.max_length_)
 			return false;

 		if (this->in_last_ == nullptr)
 		{
 			this->in_last_ = c;
 			this->in_first_ = this->in_last_;
 		}
 		else
 		{
 			this->in_last_->next_ = c;
 			this->in_last_ = c;
 		}
 		this->in_last_->next_ = nullptr;

 		return true;
 	}

 	virtual bool out_msg_push(const char* _msg) override
 	{
 		container<const char*>* c = new container<const char*>(_msg);

 		if ((this.out_qtd_ + 1) > this.max_length_)
 			return false;

 		if (this->out_last_ == nullptr)
 		{
 			this->out_last_ = c;
 			this->out_first_ = this->out_last_;
 		}
 		else
 		{
 			this->out_last_->next_ = c;
 			this->out_last_ = c;
 		}

 		this->out_last_->next_ = nullptr;

 		return true;
 	}

 	virtual const char* in_msg_get()
 	{
 		if (this.in_qtd_ < 1)
 			return nullptr;

 		container<const char*> _msg_c = this->in_first_->current_;
 		const char* _msg = _msg_c->current_;

 		this->in_first_ = _msg_c->next_;

 		delete _msg_c;

 		return _msg;
 	}

 	virtual const char* out_msg_get()
 	{
 		if (this.out_qtd_ < 1)
 			return nullptr;

 		container<const char*> _msg_c = this->out_first_->current_;
 		const char* _msg = _msg_c->current_;

 		this->out_first_ = _msg_c->next_;

 		delete _msg_c;

 		return _msg;
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