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
void List<T>::copyNodes(ListNode<T>* p, int n) //��λ��p��ʼ������n���ڵ�Ҫ����
{
	init();
	while (n--) {
		insertAsLast(p->data);
		p = p->succ;
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
T& List<T>::operator[](Rank r) const
{
	ListNode<T>* p = fisrt();
	while (0 < r--) p = p->succ;
	return p->data;
}

template<typename T>
ListNode<T>* List<T>::find(const T & e, int n, ListNode<T>* p) const//�Ӻ���ǰ��
{
	while(0<n--)
		if(e == (p=p->pred)->data) return p;
	return 0;
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