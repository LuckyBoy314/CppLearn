#include <iostream>

struct Interval
{
	int a;
	int b;
};


int Range(int A[], int n_size, Interval interval)
{
	int sum = 0;
	for (int i = 0; i < n_size; i++) {
		if (A[i] >= interval.a && A[i] <= interval.b) {
			sum++;
		}

	}
	return sum;
}
int main()
{
	using namespace std;

	int n_size, m_queries;

	cin >> n_size;
	cin >> m_queries;

	int *ptrS;
	ptrS = new  int[n_size];
	for (int i = 0; i < n_size; i++){
		cin >> ptrS[i];
	}

	Interval *ptrInterval;
	ptrInterval = new Interval[m_queries];
	for (int i = 0; i < m_queries; i++) {
		cin >> ptrInterval[i].a;
		cin >> ptrInterval[i].b;
	}

	int range;
	for (int i = 0; i < m_queries; i++) {
		range = Range(ptrS, n_size, ptrInterval[i]);
		cout << range << endl;
	}
	delete []ptrS;
	delete []ptrInterval;
	return 0;
}