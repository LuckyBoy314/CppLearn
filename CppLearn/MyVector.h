#pragma once

#define DEFAULT_CAPACITY 3
typedef int Rank;

template <typename T> 
class Vector
{
protected:
	Rank _size;  //当前规模
	int _capacity; //向量容量
	T* _elem;   //数据区

	void copyFrom(const T* A, Rank lo, Rank hi);
	void expand();
	void shrink();
	bool bubble(Rank lo, Rank hi);
	void bubbleSort(Rank lo, Rank hi);
	Rank max(Rank lo, Rank hi);
	void selectSort(Rank lo, Rank hi);
	void merge(Rank lo, Rank hi);
	void mergeSort(Rank lo, Rank hi);
	Rank partition(Rank lo, Rank hi);
	void quickSort(Rank lo, Rank hi);
	void heapSort(Rank lo, Rank hi);

public:
	//构造函数 
	Vector(int c = DEFAULT_CAPACITY, int s = 0, T v = 0) {//默认构造函数
		_elem = new T[_capacity = c];
		for (_size = 0; _size < s; _elem[_size++] = v);
	}
	Vector(const T* A, Rank n) {//由数组构造，全部用来构造
		copyFrom(A, 0, n);
	}
	Vector(const T* A, Rank lo, Rank hi) {//由数组构造，部分用来构造
		copyFrom(A, lo, hi);
	}
	Vector(const Vector<T>& v) {//复制构造函数，
		copyFrom(v._elem, 0, v._size);
	}
	Vector(const Vector<T>& v, Rank lo, Rank hi) {//复制构造函数
		copyFrom(v._elem, lo, hi);
	}

	//析构函数
	~Vector() {
		delete[] _elem;
	}

	//只读访问接口
	Rank size()const { return _size; }
	bool empty()const { return !_size; }

	int disordered()const;
	////无序查找
	Rank find(const T& e)const { return find(e, 0, _size); }
	Rank find(const T& e, Rank lo, Rank hi)const;
	////有序查找
	Rank search(const T& e, Rank lo, Rank hi)const;

	//可写接口
	////重载[]运算符,与数组的形式统一，相当于get和set函数
	T& operator[](Rank r) const;
	Vector<T>& operator=(const Vector<T>&);

	Rank insert(Rank r, const T& e);
	Rank insert(const T& e) { return insert(_size, e); }//默认在末尾插入

	T remove(Rank r);
	int remove(Rank lo, Rank hi);

	void sort(Rank lo, Rank hi);
	void sort() { sort(0, _size);}

	void unsort(Rank lo, Rank hi);
	void unsort() { unsort(0, _size);}

	int deduplicated();
	int uniquify();

	//遍历
	void traverse(void(*)(T&));
	template <typename VST>void traverse(VST&);


};

	

template<typename T>
void Vector<T>::copyFrom(const T* A, Rank lo, Rank hi) {
	_elem = new T[_capacity = 2 * (hi - lo)];
	_size = 0;
	while (lo<hi)
		_elem[_size++] = A[lo++];
}

template<typename T>
T & Vector<T>::operator[](Rank r) const {
	return _elem[r];
}

template<typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& V) {
	if (_elem) delete[]_elem;
	copyFrom(V._elem, 0, V.size());
	return *this;
}

template<typename T>
void Vector<T>::expand() {
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
void Vector<T>::shrink() {
	if (_capacity < DEFAULT_CAPACITY << 1) return;
	if (_size << 2 >_capacity) return;
	T* oldElem = _elem;
	_elem = new T[_capacity >> 1];
	for (int i = 0; i < _size; i++)
		_elem[i] = oldElem[i];
	delete[] oldElem;
}

template<typename T>
void Vector<T>::unsort(Rank lo, Rank hi) {
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
	return r;
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
