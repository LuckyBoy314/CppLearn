#pragma once
#include "MyBinTree.h"

template<typename T>
class BST :public BinTree<T> {
public:
	virtual BinNode<T>*& search(const T& e);
	virtual BinNode<T>* insert(const T& e);
	virtual bool remove(const T& e);

protected:
	BinNode<T>* _hot;
	BinNode<T>* connect34(
		BinNode<T>*, BinNode<T>*, BinNode<T>*,
		BinNode<T>*, BinNode<T>*, BinNode<T>*, BinNode<T>*);
	BinNode<T>* rotateAt(BinNode<T>* x);
};