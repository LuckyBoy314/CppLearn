#pragma once
#include "MyVector.h"

template <typename T> 
class Stack :public Vector<T>
{
public:
	//Stack(const T* A, int n) :Vector(A, n) {}
	//Stack(const Stack<T>& v) :Vector(v) {}
	using Vector::Vector;
	void push(const T& e) { insert(size(), e); }
	T pop(){ return remove(size() - 1); }
	T& top(){ return (*this)[size() - 1]; }

};

void convert(Stack<char>& S, long long n, int base);

