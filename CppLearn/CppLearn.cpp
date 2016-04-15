// MyTest.cpp : �������̨Ӧ�ó������ڵ㡣
//


#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <climits>
#include <time.h>
#include <cmath>
#include <cstdlib>
using namespace std;

#ifdef COMPILE
void printN_loop(int N)
{
	int i;
	for (i = 1; i <= N; i++)
		cout << i << endl;
}

void printN_recur(int N)
{
	if (N)
	{
		printN_recur(N - 1);
		cout << N << endl;
	}
}

/**************һԪ����ʽ�ļ���*****************/
//a[]ϵ����a[0]��a[n]����n+1��
//ֱ�ӷ���
double polynomialOne_1(int n, double a[], double x)
{
	double p = a[0];
	for (int i = 1; i <= n; i++)
		p += a[i] * pow(x, i);
	return p;
}

//�ؾ��ط�
double polynomialOne_2(int n, double a[], double x)
{
	double p = a[n];
	for (int i = n; i>0; i--)
		p = a[n - 1] + p*x;
	return p;
}
/******************************/


/***********��С���к�����*********************/
//��ķ�������ȷ�������е��Ͻ���½죬���ۼӡ����Ӷ�O(n3��
int MaxSubseqSum_1(int A[], int n)
{
	int maxSum = A[0];
	int thisSum;
	for (int i = 0; i < n; i++)       //ȷ���Ͻ�
		for (int j = i; j < n; j++) {  //�½�
			thisSum = 0;
			for (int k = i; k <= j; k++)
				thisSum += A[k];
			if (thisSum > maxSum)
				maxSum = thisSum;
		}
	return maxSum;

}

//��΢�Ľ��ķ�������ȷ���Ͻ磬Ȼ���ɨ����ۼӡ����Ӷ�O(n2)
int MaxSubseqSum_2(int A[], int n)
{
	int maxSum = A[0];
	int thisSum;
	for (int i = 0; i < n; i++) {
		thisSum = 0;
		for (int j = i; j < n; j++) {
			thisSum += A[j];
			if (thisSum > maxSum)
				maxSum = thisSum;
		}
	}

	return maxSum;

}

int MaxSubseqSum_3(int A[], int n)
{
	int maxSum = A[0];
	int thisSum = 0;
	for (int i = 0; i < n; i++) {
		thisSum += A[i];
		if (thisSum > maxSum)
			maxSum = thisSum;
		else if (thisSum < 0)
			thisSum = 0;
	}
	return maxSum;
}


void createRandArr(int A[], int n)
{
	//srand(time(NULL));
	for (int i = 0; i < n; i++) {
		A[i] = rand() % 100 - 50;
	}
}


unsigned int fib(int n)
{
	if (n == 0 || n == 1) return 1;
	return fib(n - 1) + fib(n - 2);
}

unsigned long long fib_2(int n)
{
	unsigned long long s0, s, tmp;
	s0 = 0;
	s = 1;
	while (n) {
		tmp = s0;
		s0 = s;
		s = tmp + s;
		n--;
	}
	return s;
}



/********************���Խṹ*******************************/
/********���Ա�***************/
//��������ʵ��
#define ElementType int
#define MAXSIZE 100
typedef struct {
	ElementType Data[MAXSIZE];
	int Last;
}List;

List *MakeEmpty()
{
	List* PtrL;
	PtrL = (List*)malloc(sizeof(List));
	PtrL->Last = -1;
	return PtrL;
}

int Find(ElementType X, List* PtrL)
{
	int i = 0;
	while (i <= PtrL->Last && PtrL->Data[i] != X)
		i++;
	if (i > PtrL->Last) return -1;
	else return i;
}
void Insert(ElementType X, int i, List* PtrL)
{
	if (PtrL->Last == MAXSIZE - 1) {
		cout << "�����ˣ��޷�����" << endl;
		return;
	}
	if (i<1 || i>PtrL->Last + 2) {
		cout << "λ�ò��Ϸ����޷�����" << endl;
		return;
	}
	for (int j = PtrL->Last; j >= i - 1; j--)
		PtrL->Data[j + 1] = PtrL->Data[j];
	PtrL->Data[i - 1] = X;
	PtrL->Last++;
	return;


}
//�ṹ����ʵ��
//����ʵ��+

bool isUglyNum(int n)
{
	if (n == 1) return false;
	int a[] = { 2, 3, 5 };
	while (n != 1) {
		for (int i = 0; i < 3; i++) {
			if (n%a[i] == 0) {
				n = n / a[i];
				break;
			}
			else if (n%a[i] != 0 && i == 2)
				return false;
		}
	}

	return true;
}

#endif



clock_t start, stop;// clock_t��clock()�������صı�������
double duration;//��¼���⺯������ʱ�䣬����Ϊ��λ



int main()
{
	//#define TIMETEST
#ifdef TIMETEST
	start = clock();
	//****���Գ���*********


	//****���Գ���*********
	stop = clock();

	duration = ((double)(stop - start)) / CLK_TCK;
	cout << endl << "time used:" << duration << " s\n";
#endif

	void bubbleSort(int A[], int n);
	int A[] = { 3, 4, 5, 3, 6, 9 };
	int n = sizeof(A) / sizeof(int);
	bubbleSort(A, n);

	for (int& e : A) {
		cout << e << ' ';
	}


	cin.get();
	cin.get();
	//system("pause")
	return 0;

}
