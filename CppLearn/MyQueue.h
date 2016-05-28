#pragma once

#include "MyList.h"

template <typename T>
class Queue: public List<T>{
	void enqueue(const T& e) { insertAsLast(e); }
	T dequeue() { return remove(first()); }
	T& front() { return first()->data; }
};

