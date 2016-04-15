#include "stdafx.h"
inline void swap(int& a, int& b) {
	int tmp = a;
	a = b;
	b = tmp;
}

void bubbleSort(int A[],int n){
	bool sorted = false; //
	while (!sorted){
		sorted = true;
		for (int i = 1; i < n; i++) {
			if (A[i - 1] > A[i]) {
				swap(A[i - 1], A[i]);
				sorted = false;
			}
		}
		n--;
	}
}
