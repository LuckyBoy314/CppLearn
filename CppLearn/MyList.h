#pragma once
typedef int Rank;

template <typename T> struct ListNode
{
	T data;
	ListNode<T>* pred;
	ListNode<T>* succ;

	//构造函数
	ListNode(){}
	ListNode(T e, ListNode<T>* p = 0, ListNode<T>* s = 0)
		:data(e), pred(p), succ(s){}

	//操作接口
	ListNode<T>* insertAsPred(const T& e);//在当前节点之前插入元素e
	ListNode<T>* insertAsSucc(const T& e);//在当前节点之后插入元素e
};

template<typename T> class List
{
private:
	int _size;
	ListNode<T>* header;
	ListNode<T>* tailer;
protected:
	void init();
	int clear();
	void copyNodes(ListNode<T>*, int);
	void merge(ListNode<T>* &, int, List<T>&, ListNode<T>*, int);
	void mergeSort(ListNode<T>*&, int);
	void selectionSort(ListNode<T>*, int);
public:
//构造函数
	List() {init();}//默认
	List(const List<T>& L);//复制构造函数、整体复制
	List(const List<T>& L, Rank r, Rank n);//复制列表L中第r项起的第n项
	List(ListNode<T>* p, int n);//复制列表中位置p起始的n项
//析构函数
	~List();
//只读访问接口
	int size() const { return _size; }
	bool empty()const { return _size <= 0; }

	T& operator[](Rank r)const;

	ListNode<T>* first()const { return header->succ; };
	ListNode<T>* last()const { return tailer->pred };

	bool valid(ListNode<T>* p) {
		return p && (tailer != p) && (header != p);
	}

	int disordered()const;

	ListNode<T>* find(const T& e, int n, ListNode<T>* p)const;//从当前位置p向前查找n个元素，n最好是当前位置的秩
	ListNode<T>* find(const T& e)const {
		return find(e, _size,tailer)
	}

	ListNode<T>* search(const T& e, int n, ListNode<T>* p)const;
	ListNode<T>* search(const T& e)const {
		return search(e, _size, tailer);
	}
	
	ListNode<T>* insertAsFirst(const T& e);
	ListNode<T>* insertAsLast(const T& e);
	ListNode<T>* insertPred(ListNode<T>* p, const T& e);
	ListNode<T>* insertSucc(ListNode<T>* p, const T& e);


};


