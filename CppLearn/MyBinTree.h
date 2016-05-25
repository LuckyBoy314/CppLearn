#pragma once
#include "MyStack.h"

typedef enum{RB_RED,RB_BALACK} RBColor;
#define stature(p) ((p)?p->height:-1)
/******************************************************************************************
  * BinNode״̬�����ʵ��ж�
******************************************************************************************/
#define IsRoot(x) (!((x).parent))
#define IsLChild(x) (!IsRoot(x) && (&(x) == (x).parent->lc))
#define IsRChild(x) (!IsRoot(x) && (&(x) == (x).parent->rc))
#define HasParent(x) (!IsRoot(x))
#define HasLChild(x) ((x).lc)
#define HasRChild(x) ((x).rc)
#define HasChild(x) (HasLChild(x) || HasRChild(x)) //����ӵ��һ������
#define HasBothChild(x) (HasLChild(x) && HasRChild(x)) //ͬʱӵ����������
#define IsLeaf(x) (!HasChild(x))

/******************************************************************************************
* ��BinNode�����ض���ϵ�Ľڵ㼰ָ��
******************************************************************************************/
#define sibling(p) /*�ֵ�*/ \
 ( IsLChild( * (p) ) ? (p)->parent->rc : (p)->parent->lc )
#define uncle(x) /*����*/ \
 ( IsLChild( * ( (x)->parent ) ) ? (x)->parent->parent->rc : (x)->parent->parent->lc )
#define FromParentTo(x) /*���Ը��׵�����*/ \
( IsRoot(x) ? _root : ( IsLChild(x) ? (x).parent->lc : (x).parent->rc ) )

template<typename T>
struct BinNode {
	T data;//������
	BinNode<T>* parent;//���ڵ�
	BinNode<T>* lc;//���ӽڵ�
	BinNode<T>* rc;//�Һ��ӽڵ�
	int height;
	int npl;
	RBColor color;

//���캯��
	BinNode() :parent(0), lc(0)��rc(0), height(0), npl(1), color(RB_RED) {}
	BinNode(T e, BinNode<T>* p = 0, BinNode<T>* lc = 0, BinNode<T>* rc = 0, int h = 0, int l = 1, RBColor c = RB_RED) :data(e), parent(p), lc(lc), rc(rc), height(h), npl(l), color(c) {}
//�����ӿ�
	int size();
	BinNode<T>* insertAsLC(const T&);
	BinNode<T>* insertAsRC(const T&);
	BinNode<T>* succ();
	template <typename VST> void travLevel(VST&); //������α���
	template <typename VST> void travPre(VST&); //�����������
	template <typename VST> void travIn(VST&); //�����������
	template <typename VST> void travPost(VST&); //�����������

};
template<typename T>
class BinTree
{
protected:
	int _size;
	BinNode<T>* _root;
	virtual int updateHeight(BinNode<T>* x);
	void updateHeightAbove(BinNode<T>* x);

	template<typename VST> 
	static void visitAlongLeftBranch(BinNode<T>* x, VST & visit, Stack<BinNode<T>*>& S);

	static void goAlongLeftBranch(BinNode<T>* x, Stack<BinNode<T>*>& S);

public:
	int size()const { return _size; }
	bool empty()const { return !_root; }
	BinNode<T>* root()const { return _root; }
	BinNode<T>* insertAsLC(BinNode<T>* x, const T& e);
	BinNode<T>* insertAsRC(BinNode<T>* x, const T& e);
	
	
	template <typename VST> void travPre(BinNode<T>* x, VST&); //����������� ���հ�
	template <typename VST> void travPre_v1(BinNode<T>* x, VST&); //����������� �ݹ��
	template <typename VST> void travPre_v2(BinNode<T>* x, VST&); //����������� ������1


	template <typename VST> void travIn(BinNode<T>* x, VST&); //�����������

	template <typename VST> void travPost(BinNode<T>* x, VST&); //�����������
	//template <typename VST> void travLevel(VST&); //������α���
	BinTree();
	~BinTree();
};


template<typename T>
int BinNode<T>::size()
{
	int s = 1;
	if (lc) s += lc->size();
	if (rc) s += rc->size();
	return s;
}

template<typename T>
BinNode<T>* BinNode<T>::insertAsLC(const T & e)
{
	return lc = new BinNode(e,this);
}

template<typename T>
BinNode<T>* BinNode<T>::insertAsRC(const T & e)
{
	return rc = new BinNode(e, this);
}

template<typename T>
int BinTree<T>::updateHeight(BinNode<T>* x)
{
	return x->height = 
		1 + max(stature(x->lc), stature(x->rc));
}

template<typename T>
void BinTree<T>::updateHeightAbove(BinNode<T>* x)
{
	while (x) {
		updateHeight(x);
		x = x->parent;
	}
}

template<typename T>
BinNode<T>* BinTree<T>::insertAsLC(BinNode<T>* x, const T & e)
{
	_size++;
	x->insertAsLC(e);
	updateHeightAbove(x);
	return x->lc;
}

template<typename T>
BinNode<T>* BinTree<T>::insertAsRC(BinNode<T>* x, const T & e)
{
	_size++;
	x->insertAsRC(e);
	updateHeightAbove(x);
	return x->rc;
}


template<typename T>
template<typename VST>
void BinTree<T>::travPre_v1(BinNode<T>* x,VST & visit)//�ݹ��
{
	if (x) return;
	visit(x->data);
	travPre_v1(x->lc, visit);
	travPre_v1(x->rc, visit);
}

template<typename T>
template<typename VST>
void BinTree<T>::travPre_v2(BinNode<T>* x, VST & visit)//������1
{
	Stack< BinNode<T>* > S;
	S.push(x);//������ڵ�
	while (!S.empty()) {
		x = S.pop();
		visit(x->data);
		if (HasRChild(*x)) S.push(x->rc);
		if (HasLChild(*x)) S.push(x->lc);
	}
	
}

//�ӵ�ǰ�ڵ�����������֧�������룬ֱ��û�����֧�Ľڵ㣻��;�ڵ���������������
template <typename T>
template <typename VST> //Ԫ�����͡�������
void  BinTree<T>::visitAlongLeftBranch(BinNode<T>* x, VST& visit, Stack<BinNode<T>* >& S) {
    while (x) {
       visit(x->data); //���ʵ�ǰ�ڵ�
       S.push(x->rc); //�Һ�����ջ�ݴ棨���Ż���ͨ���жϣ�����յ��Һ�����ջ��
       x = x->lc;  //�����֧����һ��
	}
}

template<typename T>
template<typename VST>
void BinTree<T>::travPre(BinNode<T>* x, VST & visit)
{
	Stack< BinNode<T>* > S;
	while (true) {
		visitAlongLeftBranch(x, visit, S);
		if (S.empty()) break;
		x = S.pop();

	}
}


template <typename T>//Ԫ�����͡�������
void  BinTree<T>::goAlongLeftBranch(BinNode<T>* x, Stack<BinNode<T>*>& S) {
	while (x) {
		S.push(x); 
		x = x->lc;  //�����֧����һ��
	}
}

template<typename T>
template<typename VST>
void BinTree<T>::travIn(BinNode<T>* x, VST & visit)
{
	Stack< BinNode<T>* > S;
	while (true) {
		goAlongLeftBranch(x, S);
		if (S.empty()) break;
		x = S.pop();
		visit(x->data);
		x = x->rc;

	}
}

template<typename T>
template<typename VST>
void BinTree<T>::travPost(BinNode<T>* x, VST & visit)
{
	Stack< BinNode<T>* > S;
	while (true) {
		while (x->rc || x->lc) {
			S.push(x);

			x = x->lc;  //�����֧����һ��
		}
		if (S.empty()) break;
		x = S.pop();
		visit(x->data); 
		x = x->parent->rc;

	}
}