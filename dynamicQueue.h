#pragma once

#include <algorithm>
#include <iostream>

#include "invalidOperationException.h"

template <class T>
class dQueue {
public:
	dQueue();
	dQueue(const dQueue<T>&);
	dQueue(unsigned const&, const T &value = static_cast<T>(0));
	~dQueue();

	dQueue<T>& operator=(dQueue<T>);

	T front();
	T back();

	bool empty();
	unsigned size() const;

	void reverse();
	int find(const T&);

	void push(const T&);
	void pop();

	friend std::ostream& operator <<(std::ostream &os, const dQueue<T> &dQueueObj) {
		typename dQueue<T>::node *temp = dQueueObj.head;

		while(temp != nullptr) {
			os << temp->data << ' ';
			temp = temp->next;
		}

		os << std::endl;

		delete temp;

		return os;
	}

	T& operator[](unsigned const&);
	const T& operator[](unsigned const&) const;

private:
	struct node
	{
		T data;
		node *next;
	};

 	node *head;
 	node *tail;
 	unsigned mSize;
};
