#ifndef _adjListGraph_h_
#define _adjListGraph_h_

#include <iostream>
using namespace std;

class adjListGraph
{
private:
	struct edgeNode{    //�ڽӱ��д洢�ߵĽ����
		int end;        //�յ���
		int weight;     //�ߵ�Ȩֵ
		edgeNode *next;
		edgeNode(int v, int w, edgeNode *p=NULL):end(v),weight(w),next(p){}
	};

	struct verNode{      //���涥�������Ԫ������
		int ver;         //����ֵ
		edgeNode *head;  //��Ӧ�������ͷָ��
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
	
	bool insert(int u, int v, int w);// ����һ����uָ��vȨֵΪw�ĵ�
	int find(int start, int M); // ���ش�start��ʼ����ΪM�ļ�·������

};

void adjListGraph::clear(edgeNode *t)   //ɾ��һ���߽��
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

bool adjListGraph::insert(int u, int v, int w)  //����һ����
{
	verList[u].head=new edgeNode(v,w,verList[u].head);
	++edges;
	return true;
}

int adjListGraph::find(int start, int M)
{
	int n=0;
	verList[start].visited=true;
	DFS(start,M,n);    //���øĽ����DFS����
	verList[start].visited=false;  //��ԭ���ʺ�Ľ��
	return n;
}

void adjListGraph::DFS(int v, int M, int &n)
{
	if(M==0) ++n;
	for(edgeNode *p=verList[v].head; p!=NULL; p=p->next)
		if(!verList[p->end].visited){
			verList[p->end].visited=true;   //���Ǻ�
			DFS(p->end, M-p->weight, n);    //�ݹ����
			verList[p->end].visited=false;  //�����Ǻ�
		}
}

#endif