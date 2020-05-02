#pragma once

#include <cassert>
/*
-------------TO-DO-LIST-------------
	+ copy semantic
	+ move semantic
	+ operator = with rvalue
	+ operator*
	+ operator->
	+ function get()
	+ reset
-------------TO-DO-LIST-------------
*/
namespace my {

	template <class T>
	class shered_ptr {

		struct proxy {
			size_t counter_;
			T* data_;

			 proxy (T* init_data);
			~proxy ();
		};
		
		proxy* proxy_point_;

		void disconnectProxy ();

	public:
		shered_ptr ();
		shered_ptr (T* init_data);
		shered_ptr (const shered_ptr& right);
		shered_ptr (shered_ptr&& right);

		~shered_ptr ();

		shered_ptr& operator = (const shered_ptr& right);
		shered_ptr& operator = (shered_ptr&& right);

		T& operator * ();
		T* operator -> ();
		T* get ();

		void reset ();
		void reset (T* new_point);

	}; // class shered_ptr

	
	template <class T>
	shered_ptr<T>::shered_ptr (): 
		proxy_point_ (0)
	{}

	template <class T>
	shered_ptr<T>::shered_ptr (T* init_data):
		proxy_point_ (new proxy (init_data))
	{
		proxy_point_->counter_++;
	}

	template <class T>
	shered_ptr<T>::~shered_ptr () {
		//printf ("Counter %d\n", proxy_point_->counter_);
		disconnectProxy ();
	}


	template <class T>
	shered_ptr<T>& shered_ptr<T>::operator=(const shered_ptr& right) {
		if (this->proxy_point_ != right.proxy_point_) {
			printf ("this %p right %p\n", this, &right);
			disconnectProxy ();

			this->proxy_point_ = right.proxy_point_;
			proxy_point_->counter_++;
		}
		return *this;
	}

	template <class T>
	shered_ptr<T>& shered_ptr<T>:: operator = (shered_ptr&& right) {
		if (this->proxy_point_ != right.proxy_point_) {
			printf ("this %p right %p\n", this, &right);
			disconnectProxy ();

			this->proxy_point_ = right.proxy_point_;
			right.proxy_point_  = nullptr;
		}
		return *this;
	}

	template <class T>
	shered_ptr<T>::shered_ptr (const shered_ptr& right) {
		this->proxy_point_ = right.proxy_point_;
		proxy_point_->counter_++;
		printf ("Copy counter %d\n", proxy_point_->counter_);
	}

	template <class T>
	shered_ptr<T>::shered_ptr (shered_ptr&& right) {
		this->proxy_point_ = right.proxy_point_;
		right.proxy_point_ = 0;
	}

	template <class T>
	void shered_ptr<T>::disconnectProxy () {
		if (proxy_point_ != nullptr) {
			if (proxy_point_->counter_ == 1)
				delete proxy_point_;
			else
				proxy_point_->counter_--;
		}
	}

	template <class T>
	T& shered_ptr<T>::operator* () {
		assert (proxy_point_ != 0);
		return *(proxy_point_->data_);
	}

	template <class T>
	T* shered_ptr<T>::operator-> () {
		assert (proxy_point_ != 0);
		return proxy_point_->data_;
	}

	template <class T>
	T* shered_ptr<T>::get () {
		assert (proxy_point_ != 0);
		return proxy_point_->data_;
	}

	template <class T>
	void shered_ptr<T>::reset () {
		assert (proxy_point_ != 0);
		delete proxy_point_->data_;
		proxy_point_->data_ = 0;
	}

	template <class T>
	void shered_ptr<T>::reset (T* new_point) {
		assert (proxy_point_ != 0);
		delete proxy_point_->data_;
		proxy_point_->data_ = new_point;
	}
	// --------------it-was-realisation-of-shered_ptr----------------

	template <class T>
	shered_ptr<T>::proxy::proxy (T* init_data):
		counter_ (0),
		data_ (init_data) 
	{}

	template <class T>
	shered_ptr<T>::proxy::~proxy () {
		delete data_;
		printf ("Desctructor proxy\n");
		data_ = nullptr;
	}

}