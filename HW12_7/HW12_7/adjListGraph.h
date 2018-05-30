#ifndef _adjListGraph_h_
#define _adjListGraph_h_

#include <iostream>
using namespace std;

class adjListGraph
{
private:
	struct edgeNode{    //邻接表中存储边的结点类
		int end;        //终点编号
		int weight;     //边的权值
		edgeNode *next;
		edgeNode(int v, int w, edgeNode *p=NULL):end(v),weight(w),next(p){}
	};

	struct verNode{      //保存顶点的数据元素类型
		int ver;         //顶点值
		edgeNode *head;  //对应单链表的头指针
		bool visited;
		verNode():head(NULL),visited(false){}
	};

	verNode *verList;
	int size,edges;
	void clear(edgeNode *t);
	void DFS(int v, int M, int &n);

public:
	adjListGraph(int vSize, const int d[]):size(vSize),edges(0){verList=new verNode[size]; for(int i=0; i<size; ++i) verList[i].ver=d[i];}
	~adjListGraph();
	
	bool insert(int u, int v, int w);// 插入一个从u指向v权值为w的点
	int find(int start, int M); // 返回从start开始长度为M的简单路径条数

};

void adjListGraph::clear(edgeNode *t)   //删除一个边结点
{
	if(t!=NULL){
		clear(t->next);
		delete t;
		t=NULL;
	}
}

adjListGraph::~adjListGraph()
{
	for(int i=0; i<size; ++i) clear(verList[i].head);
	delete[] verList;
}

bool adjListGraph::insert(int u, int v, int w)  //插入一条边
{
	verList[u].head=new edgeNode(v,w,verList[u].head);
	++edges;
	return true;
}

int adjListGraph::find(int start, int M)
{
	int n=0;
	verList[start].visited=true;
	DFS(start,M,n);    //调用改进后的DFS函数
	verList[start].visited=false;  //还原访问后的结点
	return n;
}

void adjListGraph::DFS(int v, int M, int &n)
{
	if(M==0) ++n;
	for(edgeNode *p=verList[v].head; p!=NULL; p=p->next)
		if(!verList[p->end].visited){
			verList[p->end].visited=true;   //做记号
			DFS(p->end, M-p->weight, n);    //递归遍历
			verList[p->end].visited=false;  //消除记号
		}
}

#endif