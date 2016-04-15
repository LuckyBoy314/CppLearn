#include "stdafx.h"
#include "MyVector.h"	

template<typename T>
void Vector<T>::copyFrom(const T* A, Rank lo, Rank hi) {
	_elem = new T[_capacity = 2 * (hi - lo)];
	_size = 0;
	while (lo<hi)
		_elem[size++] = A[lo++];
} 

template<typename T>
T & Vector<T>::operator[](Rank r) const {
	return _elem[r];
}

template<typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& V){
	if (_elem) delete[]_elem;
	copyFrom(V._elem, 0, V.size());
	return *this;
}

template<typename T>
void Vector<T>::expand(){
	if (_size < _capacity) return;
	if (_capacity < DEFAULT_CAPACITY)
		_capacity = DEFAULT_CAPACITY;
	T* oldElem = _elem;
	_elem = new T[_capacity <<= 1];
	for (int i = 0; i < _size; i++)
		_elem[i] = oldElem[i];
	delete[] oldElem;
}

template<typename T>
void Vector<T>::shrink(){
	if (_capacity < DEFAULT_CAPACITY << 1) return;
	if (_size << 2 >_capacity) return;
	T* oldElem = _elem;
	_elem = new T[_capacity >> 1];
	for (int i = 0; i < _size; i++)
		_elem[i] = oldElem[i];
	delete[] oldElem;
}

template<typename T>
void Vector<T>::unsort(Rank lo, Rank hi){
	T* V = _elem + lo;
	for (Rank i = hi - lo; i > 0; i--)
		swap(V[i - 1], V[rand() % i]);
}

template<typename T>
Rank Vector<T>::find(const T & e, Rank lo, Rank hi) const {
	while ((lo < hi--) && (e != _elem[hi]));
	return hi;
}

template<typename T>
Rank Vector<T>::insert(Rank r, const T & e)
{
	expand();
	for (int i = _size; i > r; i--)
		_elem[i] = _elem[i - 1];

	_elem[r] = e;
	_size++;
	ruturn r;
}

template<typename T>
int Vector<T>::remove(Rank lo, Rank hi)
{
	if (lo == hi) return 0;
	while (hi < _size)
		_elem[lo++] = _elem[hi++];
	_size = lo;//删除以后要对向量大小进行更新
	shrink();
	return hi - lo;
}

template<typename T>
T Vector<T>::remove(Rank r)
{ 
	T e = _elem[r];
	remove(r, r + 1);
	return e;
}

template<typename T>
int Vector<T>::deduplicated()
{
	int oldSize = _size;
	Rank i = 1;
	while (i < _size)
		(find(_elem[i], 0, i) < 0) ? i++ : remove(i);
	return oldSize - _size;
}
