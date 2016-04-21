#include "stdafx.h"
#include "MyList.h"	

template<typename T>
ListNode<T>* ListNode<T>::insertAsSucc(const T & e)
{
	ListNode<T>* x = new ListNode(e, this, succ);
	succ->pred = x;
	succ = x;
	return x;
}

template<typename T>
ListNode<T>* ListNode<T>::insertAsPred(const T & e)
{
	ListNode<T>* x = new ListNode(e, pred,this);
	pred->succ = x;
	pred = x;
	return x;
}

template<typename T>
void List<T>::init()
{
	header = new ListNode<T>;
	tailer = new ListNode<T>;
	header->succ = tailer; header->pred = 0;
	tailer->pred = header; tailer->succ = 0;
	_size = 0;
}

template<typename T>
int List<T>::clear()
{
	int oldSize = _size;
	while (0 < _size)//remove函数内含了_size-1，因此无需_size--；
		remove(header->succ);
	return oldSize;
}

template<typename T>
void List<T>::copyNodes(ListNode<T>* p, int n) //从位置p开始，共有n个节点要复制
{
	init();
	while (n--) {
		insertAsLast(p->data);
		p = p->succ;
	}
}

template<typename T>
void List<T>::selectionSort(ListNode<T>* p, int n)
{
	ListNode<T>* head = p->pred;
	ListNode<T>* tail = p;
	for (int i = 0; i < n; i++)
		tail = tail->succ;

	while (1 < n) {
		insertBefore(tail, remove(selectMax(head->succ, n));//insertBefore和remove的操作需要动态分配和删除内存，实际时间开销较大
		tail = tail->pred;								    //应该考虑优化
		n--;
	}
}

template<typename T>
List<T>::List(const List<T>& L)
{
	copyNodes(L.first(),L._size)
}

template<typename T>
List<T>::List(const List<T>& L, Rank r, Rank n)
{
	copyNodes(L[r], n);
}

template<typename T>
List<T>::List(ListNode<T>* p, int n)
{
	copyNodes(p, n);
}

template<typename T>
List<T>::~List()
{
	clear();
	delete header;
	delete tailer;
}

template<typename T>
T& List<T>::operator[](Rank r) const
{
	ListNode<T>* p = fisrt();
	while (0 < r--) p = p->succ;
	return p->data;
}

template<typename T>
ListNode<T>* List<T>::find(const T & e, int n, ListNode<T>* p) const//从后往前找
{
	while(0<n--)
		if(e == (p=p->pred)->data) return p;
	return 0;
}

template<typename T>//返回不大于e的最后位置
ListNode<T>* List<T>::search(const T & e, int n, ListNode<T>* p) const
{
	while (0<n--){
		if (((p = p->pred)->data) <= e)
			break;
	}
	return p;
}

template<typename T>
ListNode<T>* List<T>::insertAsFirst(const T & e)
{
	_size++;
	return header->insertAsSucc(e);
}

template<typename T>
ListNode<T>* List<T>::insertAsLast(const T & e)
{
	_size++;
	return tailer->insertAsPred(e);
}

template<typename T>
ListNode<T>* List<T>::insertBefore(ListNode<T>* p, const T & e)
{
	_size++;
	return p->insertAsPred(e);
}

template<typename T>
ListNode<T>* List<T>::insertAfter(ListNode<T>* p, const T & e)
{
	_size++;
	return p->insertAsSucc(e);
}

template<typename T>
T List<T>::remove(ListNode<T>* p)
{
	T e = p->data;
	p->succ->pred = p->pred;
	p->pred->succ = p->succ;
	_size--;
	delete p;
	return e;
}

template<typename T>
int List<T>::deduplicate()
{
	if（_size < 2）return 0;
	int oldSize = _size;
	ListNode<T>* p = first();
	Rank r = 1;
	while (tailer != (p = p->succ)) {
		ListNode<T>* q = find(p->data, r, p);
		q ? remove(q) : r++;
	}
	return oldSize - _size;
}

template<typename T>
int List<T>::uniquify()
{
	if (_size < 2)return 0;
	int oldSize = _size;
	ListNode<T>* p = first();
	ListNode<T>* q;
	while (tailer != (q = p->succ)) {
		if (p->data != q->data) 
			p = q;
		else
			remove(q);
	}

	return oldSize - _size;
}

template<typename T>
void List<T>::sort(ListNode<T>* p, int n)//以位置p为起点的向后n个元素（包括p位置上的元素）需要排序
{
	switch (rand()%3){
		case 1:insertionSort(p, n); break;//插入排序
		case 2:selectionSort(p, n); break;//选择排序
		default: mergeSort(p, n); break;//归并排序
	}
}
