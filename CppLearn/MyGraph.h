#pragma once
#include "MyVector.h"

typedef enum { UNDISCOVERED, DISCOVERED, VISITED } VStatus;//�����״̬
typedef enum{UNDETERMINED,TREE,CROSS,FORWARD,BACKWARD} EType;//�ߵ����ͣ��ڱ������ֵ�����������

template <typename Tv>
struct Vertex{//������
	Tv data;//������
	int inDegree, outDegree;//�������
	VStatus status;
	int dTime, fTime;//ʱ���ǩ
	int parent;//�ڱ������еĸ��ڵ�
	int priority;//�ڱ������е����ȼ������ͨ·�����˿�ߣ�

	Vertex(const Tv& d):
		data(d),inDegree(0),outDegree(0),status(UNDISCOVERED),
			dTime(-1),fTime(-1),parent(-1),priority(INT_MAX){}
};

template <typename Te>
struct Edge {//����
	Te data;
	int weight;
	EType type;
	Edge(const Te& d,int w):data(d),weight(w),type(UNDETERMINED){}
};

/*ͼ��*/
template<typename Tv,typename Te>
class Graph {
private:
	void reset() {
		for (int i = 0; i < n; i++) {
			status(i) = UNDISCOVERED;
			dTime(i) = fTime(i) = -1;
			parent(i) = -1;
			priority(i) = INT_MAX;
			for (int j = 0; j < n; j++) 
				if (exists(i, j)) type(i, j) = UNDETERMINED;
		}
	}

	void BFS(int, int&);//����ͨ�򣩹�����������㷨
	void DFS(int, int&);//����ͨ��������������㷨
public:
//����
	int n;//��������
	virtual int insert(const Tv&) = 0;
	virtual Tv remove(int) = 0;
	virtual Tv& vertex(int) = 0;
	virtual int inDegree(int) = 0;
	virtual int outDegree(int) = 0;
	virtual int firstNbr(int) = 0;
	virtual int nextNbr(int, int) = 0;
	virtual VStatus& status(int) = 0;
	virtual int& dTime(int) = 0;
	virtual int& fTime(int) = 0;
	virtual int& parent(int) = 0;
	virtual int& priority(int) = 0;


//��
	int e;//������
	virtual bool exists(int, int) = 0;
	virtual void insert(const Te&, int, int, int) = 0;
	virtual Te remove(int, int) = 0;
	virtual EType& type(int, int) = 0;
	virtual Te& edge(int, int) = 0;
	virtual int& weight(int, int) = 0;

//�㷨
	void bfs(int);//������������㷨
	void dfs(int);//������������㷨
};


/*�ڽӾ�����*/
template<typename Tv,typename Te>
class GraphMatrix :public Graph<Tv, Te> {
private:
	Vector< Vertex<Tv> > V;//���㼯
	Vector< Vector<Edge<Te>* > > E;//�߼�
public:
	GraphMatrix() { n = e = 0; }
	~GraphMatrix() {
		for (int j = 0; j < n; j++)
			for (int k = 0; k < n; k++)
				delete E[j][k];
	}
//����Ļ�������
	//��ѯ��i������
	virtual Tv& vertex(int i) { return V[i].data; }
	virtual int inDegree(int i) { return V[i].inDegree; }
	virtual int outDegree(int i) {return V[i].outDegree; }
	virtual int firstNbr(int i) { return nextNbr(i, n); }	
	virtual int nextNbr(int i, int j);
	virtual VStatus& status(int i) { return V[i].status; }
	virtual int& dTime(int i) { return V[i].dTime; }
	virtual int& fTime(int i) { return V[i].fTime; }
	virtual int& parent(int i) { return V[i].parent; }
	virtual int& priority(int i) { return V[i].priority; }

	//����Ķ�̬����
	virtual int insert(const Tv& vertex);
	virtual Tv remove(int i);

//�ߵĻ�������
	//�ߵ�ȷ�ϲ���
	virtual bool exists(int i, int j) {
		return (0 <= i) && (i < n) && (0 <= j) && (j < n) && E[i][j] != NULL;
	}
	//��ѯ����i�Ͷ���j֮�������
	virtual EType& type(int i, int j) { return E[i][j]->type; }
	virtual Te& edge(int i, int j) { return E[i][j]->data; }
	virtual int& weight(int i, int j) { return E[i][j]->weight; }
	//�ߵĶ�̬����
	virtual void insert(const Te& edge, int w, int i, int j);
	virtual Te remove(int i, int j);

};

template<typename Tv, typename Te>
int GraphMatrix<Tv, Te>::nextNbr(int i,int j){
	while ((-1 < j) && (!exists(i, --j)));
	return j;
}

template<typename Tv, typename Te>
void GraphMatrix<Tv, Te>::insert(const Te & edge, int w, int i, int j){
	if (exists(i, j))return;
	E[i][j] = new Edge<Te>(edge, w);
	e++;
	V[i].outDegree++;
	V[j].inDegree++;

}

template<typename Tv, typename Te>
inline Te GraphMatrix<Tv, Te>::remove(int i, int j)
{
	Te eback = edge(i, j);
	delete E[i][j];
	E[i][j] = NULL;
	e--;
	V[i].outDegree--;
	V[i].inDegree--;
	return eback;
}

template<typename Tv, typename Te>
void Graph<Tv, Te>::BFS(int v, int & clock){//v��ʾ��v�����㣬����������ʼ����
	Queue<int> Q;
	status(v) = DISCOVERED;
	Q.enqueue(v);
	while (!Q.empty()){
		int v = Q.dequeue();
		dTime(v) = ++clock;
		for(int u = firstNbr(v); u>-1;u=nextNbr(v,u))
			if (status(u) == UNDISCOVERED) {
				status(u) = DISCOVERED;
				Q.enqueue(u);
				type(v, u) = TREE;
				parent(u) = v;
			}
			else {
				type(v, u) = CROSS;
			}

			//�������������Զ����v����ʵ����
			status(v) = VISITED;

	}
}

template<typename Tv, typename Te>
void Graph<Tv, Te>::DFS(int v, int& clock){
	dTime(v) = ++clock;
	status(v) = DISCOVERED;
	for(int u = firstNbr(v);u > -1; u=nextNbr(v,u))
		switch (status(u)) {
		case UNDISCOVERED:
			type(v, u) = TREE;
			parent(u) = v;
			DFS(u, clock);
			break;
		case DISCOVERED:
			type(v, u) = BACKWARD;
			break;
		default:
			type(v, u) = (dTime(v) < dTime(u)) ? FORWARD : CROSS;
			break;
		}
	status(v) = VISITED;
	fTime(v) = ++clock;
}

template<typename Tv, typename Te>
void Graph<Tv, Te>::bfs(int s){
	reset();
	int clock = 0;
	int v = s;
	do {
		if (UNDISCOVERED == status(v))
			BFS(v, clock);
	} while (s != (v = ++v%n));
}

template<typename Tv, typename Te>
void Graph<Tv, Te>::dfs(int s){
	reset();
	int clock = 0;
	int v = s;
	do {
		if (UNDISCOVERED == status(v))
			DFS(v, clock);
	} while (s != (v = ++v%n));
}
