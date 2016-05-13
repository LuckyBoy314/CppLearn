#pragma once

#define DEFAULT_CAPACITY 3
typedef int Rank;

template <typename T> 
class Vector
{
protected:
	Rank _size;  //��ǰ��ģ
	int _capacity; //��������
	T* _elem;   //������

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
	//���캯�� 
	Vector(int c = DEFAULT_CAPACITY, int s = 0, T v = 0) {//Ĭ�Ϲ��캯��
		_elem = new T[_capacity = c];
		for (_size = 0; _size < s; _elem[_size++] = v);
	}
	Vector(const T* A, Rank n) {//�����鹹�죬ȫ����������
		copyFrom(A, 0, n);
	}
	Vector(const T* A, Rank lo, Rank hi) {//�����鹹�죬������������
		copyFrom(A, lo, hi);
	}
	Vector(const Vector<T>& v) {//���ƹ��캯����
		copyFrom(v._elem, 0, v._size);
	}
	Vector(const Vector<T>& v, Rank lo, Rank hi) {//���ƹ��캯��
		copyFrom(v._elem, lo, hi);
	}

	//��������
	~Vector() {
		delete[] _elem;
	}

	//ֻ�����ʽӿ�
	Rank size()const { return _size; }
	bool empty()const { return !_size; }

	int disordered()const;
	////�������
	Rank find(const T& e)const { return find(e, 0, _size); }
	Rank find(const T& e, Rank lo, Rank hi)const;
	////�������
	Rank search(const T& e, Rank lo, Rank hi)const;

	//��д�ӿ�
	////����[]�����,���������ʽͳһ���൱��get��set����
	T& operator[](Rank r) const;
	Vector<T>& operator=(const Vector<T>&);

	Rank insert(Rank r, const T& e);
	Rank insert(const T& e) { return insert(_size, e); }//Ĭ����ĩβ����

	T remove(Rank r);
	int remove(Rank lo, Rank hi);

	void sort(Rank lo, Rank hi);
	void sort() { sort(0, _size);}

	void unsort(Rank lo, Rank hi);
	void unsort() { unsort(0, _size);}

	int deduplicated();
	int uniquify();

	//����
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
	_size = lo;//ɾ���Ժ�Ҫ��������С���и���
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
