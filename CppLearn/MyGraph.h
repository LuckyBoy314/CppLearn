#pragma once
#include "MyVector.h"

typedef enum { UNDISCOVERED, DISCOVERED, VISITED } VStatus;//顶点的状态
typedef enum{UNDETERMINED,TREE,CROSS,FORWARD,BACKWARD} EType;//边的类型，在遍历树种的所属的类型

template <typename Tv>
struct Vertex{//顶点类
	Tv data;//数据域
	int inDegree, outDegree;//出、入度
	VStatus status;
	int dTime, fTime;//时间标签
	int parent;//在遍历树中的父节点
	int priority;//在遍历树中的优先级（最短通路、极端跨边）

	Vertex(const Tv& d):
		data(d),inDegree(0),outDegree(0),status(UNDISCOVERED),
			dTime(-1),fTime(-1),parent(-1),priority(INT_MAX){}
};

template <typename Te>
struct Edge {//边类
	Te data;
	int weight;
	EType type;
	Edge(const Te& d,int w):data(d),weight(w),type(UNDETERMINED){}
};

/*图类*/
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

	void BFS(int, int&);//（连通域）广度优先搜索算法
	void DFS(int, int&);//（连通域）深度优先搜索算法
public:
//顶点
	int n;//顶点总数
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


//边
	int e;//边总数
	virtual bool exists(int, int) = 0;
	virtual void insert(const Te&, int, int, int) = 0;
	virtual Te remove(int, int) = 0;
	virtual EType& type(int, int) = 0;
	virtual Te& edge(int, int) = 0;
	virtual int& weight(int, int) = 0;

//算法
	void bfs(int);//广度优先搜索算法
	void dfs(int);//深度优先搜索算法
};


/*邻接矩阵类*/
template<typename Tv,typename Te>
class GraphMatrix :public Graph<Tv, Te> {
private:
	Vector< Vertex<Tv> > V;//顶点集
	Vector< Vector<Edge<Te>* > > E;//边集
public:
	GraphMatrix() { n = e = 0; }
	~GraphMatrix() {
		for (int j = 0; j < n; j++)
			for (int k = 0; k < n; k++)
				delete E[j][k];
	}
//顶点的基本操作
	//查询第i个顶点
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

	//顶点的动态操作
	virtual int insert(const Tv& vertex);
	virtual Tv remove(int i);

//边的基本操作
	//边的确认操作
	virtual bool exists(int i, int j) {
		return (0 <= i) && (i < n) && (0 <= j) && (j < n) && E[i][j] != NULL;
	}
	//查询顶点i和顶点j之间的联边
	virtual EType& type(int i, int j) { return E[i][j]->type; }
	virtual Te& edge(int i, int j) { return E[i][j]->data; }
	virtual int& weight(int i, int j) { return E[i][j]->weight; }
	//边的动态操作
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
void Graph<Tv, Te>::BFS(int v, int & clock){//v表示第v个顶点，是搜索的起始顶点
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

			//………………对顶点的v的真实处理
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
