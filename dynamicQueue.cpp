// A dinamikus varakozasi sor definicioja

#include "dynamicQueue.h"

template <class T>
dQueue<T>::dQueue() : head(nullptr), tail(nullptr), mSize(0) { }

template <class T>
dQueue<T>::dQueue(const dQueue<T> &dQueueObj) : head(nullptr), tail(nullptr), mSize(0) {
	if(dQueueObj.head == nullptr) {
		return;
	}

	node *temp = dQueueObj.head;

	do {
		push(temp->data);
		temp = temp->next;
	} while(temp != nullptr);
}

template <class T>
dQueue<T>::dQueue(unsigned const &numOfNodes, const T &value) :head(nullptr), tail(nullptr), mSize(0) {
	if(numOfNodes == 0) {
		return;
	}

	unsigned kontor = 0;

	while(kontor < numOfNodes) {
		push(value);
		++kontor;
	}
}

template <class T>
dQueue<T>::~dQueue() {
	typename dQueue<T>::node *current = this->head;

	while(current != nullptr) {
		typename dQueue<T>::node *old = current;
		current = current->next;
		delete old;
	}
}

template <class T>
dQueue<T>& dQueue<T>::operator=(dQueue<T> dQueueObj) {
	if(this == &dQueueObj) {
		return *this;
	}

	std::swap(dQueueObj.head, this->head);
	std::swap(dQueueObj.tail, this->tail);
	std::swap(dQueueObj.mSize, this->mSize);

	return *this;
}

template <class T>
T dQueue<T>::front() {
	return (this->head)->data;
}

template <class T>
T dQueue<T>::back() {
	return (this->tail)->data;
}

template <class T>
bool dQueue<T>::empty() {
	return this->mSize == 0;
}

template <class T>
unsigned dQueue<T>::size() const {
	return this->mSize;
}

template <class T>
void dQueue<T>::reverse() {
	if(this->mSize < 2) {
		return;
	}

	typename dQueue<T>::node *prevWalker = this->head;
	typename dQueue<T>::node *currWalker = this->head->next;

	while(currWalker != nullptr) {
		typename dQueue<T>::node *temp = currWalker;
		currWalker = currWalker->next;
		temp->next = prevWalker;
		prevWalker = temp;
	}

	this->head->next = nullptr;

	this->tail = this->head;
	this->head = prevWalker;
}

template <class T>
int dQueue<T>::find(const T &key) {
	unsigned kontor = 0;
	typename dQueue<T>::node *temp = this->head;

	while(temp != nullptr && temp->data != key) {
		temp = temp->next;
		++kontor;
	}

	return temp == nullptr ? -1 : kontor;
}

template <class T>
void dQueue<T>::push(const T &value) {
	typename dQueue<T>::node *temp = new node();

	temp->data = value;
	temp->next = nullptr;

	if(this->head == nullptr) {
		this->head = temp;
		this->tail = temp;
	}
	else {
		(this->tail)->next = temp;
		this->tail = temp;
	}

	++(this->mSize);
}

template <class T>
void dQueue<T>::pop() {
	if(this->head == nullptr) {
		throw InvalidOperationException("the queue is empty!");
	}

	typename dQueue<T>::node *temp = this->head;
	this->head = (this->head)->next;
	delete temp;

	--(this->mSize);
}

template <class T>
T& dQueue<T>::operator[](unsigned const &index) {
	if(index >= this->mSize) {
		throw std::invalid_argument("segfault: there's no such index!");
	}

	unsigned kontor = 0;
	typename dQueue<T>::node *temp = this->head;

	while(kontor < index) {
		temp = temp->next;
		++kontor;
	}

	return temp->data;
}

template <class T>
const T& dQueue<T>::operator[](unsigned const &index) const {
	if(index >= this->mSize) {
		throw std::invalid_argument("segfault: there's no such index!");
	}

	unsigned kontor = 0;
	typename dQueue<T>::node *temp = this->head;

	while(kontor < index) {
		temp = temp->next;
		++kontor;
	}

	return temp->data;
}

template class dQueue<bool>;
template class dQueue<unsigned>;
template class dQueue<int>;
template class dQueue<float>;
template class dQueue<double>;
template class dQueue<std::string>;
