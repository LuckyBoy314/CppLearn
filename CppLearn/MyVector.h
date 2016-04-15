#pragma once

#define DEFAULT_CAPACITY 3
typedef int Rank;

template <typename T> class  Vector
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

