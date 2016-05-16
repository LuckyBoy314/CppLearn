#pragma once

typedef enum{RB_RED,RB_BALACK} RBColor;
#define stature(p) ((p)?p->height:-1)
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
public:
	int size()const { return _size; }
	bool empty()const { return !_root; }
	BinNode<T>* root()const { return _root; }
	BinNode<T>* insertAsLC(BinNode<T>* x, const T& e);
	BinNode<T>* insertAsRC(BinNode<T>* x, const T& e);
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

BinNode<T>* BinTree<T>::insertAsRC(BinNode<T>* x, const T & e)
{
	_size++;
	x->insertAsRC(e);
	updateHeightAbove(x);
	return x->rc;
}
