// MyTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
	

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

/**************一元多项式的计算*****************/
//a[]系数从a[0]到a[n]，共n+1项
//直接方法
double polynomialOne_1(int n, double a[], double x)
{
	double p = a[0];
	for (int i = 1; i <= n; i++)
		p += a[i] * pow(x, i);
	return p;
}

//秦九韶法
double polynomialOne_2(int n, double a[], double x)
{
	double p = a[n];
	for (int i = n; i>0; i--)
		p = a[n - 1] + p*x;
	return p;
}
/******************************/


/***********最小子列和问题*********************/
//最笨的方法，先确定子序列的上界和下届，在累加。复杂度O(n3）
int MaxSubseqSum_1(int A[], int n)
{
	int maxSum = A[0];
	int thisSum;
	for (int i = 0; i < n; i++)       //确定上界
		for (int j = i; j < n; j++) {  //下界
			thisSum = 0;
			for (int k = i; k <= j; k++)
				thisSum += A[k];
			if (thisSum > maxSum)
				maxSum = thisSum;
		}
	return maxSum;

}

//稍微改进的方法，先确定上界，然后边扫描边累加。复杂度O(n2)
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



#endif



clock_t start, stop;// clock_t是clock()函数返回的变量类型
double duration;//记录被测函数运行时间，以秒为单位

void f(int* A, int n, int& max, int& max_second) {
	if (!n) return;
	int tmp = *A;
	if (tmp>max)
		max = tmp;
	if (tmp>max_second && tmp<max)
		max_second = tmp;

	f(A++, --n, max, max_second);
}

int main()
{
	//#define TIMETEST
#ifdef TIMETEST
	start = clock();
	//****测试程序*********


	//****测试程序*********
	stop = clock();

	duration = ((double)(stop - start)) / CLK_TCK;
	cout << endl << "time used:" << duration << " s\n";
#endif

	int A[] = { 1,2,4,5,8 };
	int max = 0, max_second = 0;
	f(A, 5, max, max_second);
	std::cout << max << " " << max_second << std::endl;

	cin.get();
	cin.get();
	//system("pause")
	return 0;

}
