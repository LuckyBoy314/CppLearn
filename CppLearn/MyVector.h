#pragma once

#define DEFAULT_CAPACITY 3
typedef int Rank;

template <typename T> class  Vector
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

