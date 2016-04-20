#pragma once
typedef int Rank;

template <typename T> struct ListNode
{
	T data;
	ListNode<T>* pred;
	ListNode<T>* succ;

	//���캯��
	ListNode(){}
	ListNode(T e, ListNode<T>* p = 0, ListNode<T>* s = 0)
		:data(e), pred(p), succ(s){}

	//�����ӿ�
	ListNode<T>* insertAsPred(const T& e);//�ڵ�ǰ�ڵ�֮ǰ����Ԫ��e
	ListNode<T>* insertAsSucc(const T& e);//�ڵ�ǰ�ڵ�֮�����Ԫ��e
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
//���캯��
	List() {init();}//Ĭ��
	List(const List<T>& L);//���ƹ��캯�������帴��
	List(const List<T>& L, Rank r, Rank n);//�����б�L�е�r����ĵ�n��
	List(ListNode<T>* p, int n);//�����б���λ��p��ʼ��n��
//��������
	~List();
//ֻ�����ʽӿ�
	int size() const { return _size; }
	bool empty()const { return _size <= 0; }

	T& operator[](Rank r)const;

	ListNode<T>* first()const { return header->succ; };
	ListNode<T>* last()const { return tailer->pred };

	bool valid(ListNode<T>* p) {
		return p && (tailer != p) && (header != p);
	}

	int disordered()const;

	ListNode<T>* find(const T& e, int n, ListNode<T>* p)const;//�ӵ�ǰλ��p��ǰ����n��Ԫ�أ�n����ǵ�ǰλ�õ���
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


