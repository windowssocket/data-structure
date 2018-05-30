#include <iostream>

using namespace std;

//链表队列类
template <class elemType>
class linkQueue
{
private:
	struct node
	{
		elemType data;
		node *next;
		node(const elemType &x, node *N=NULL)
		{
			data=x;
			next=N;
		}
		node():next(NULL){}
		~node() {}
	};
	node *front, *rear;

public:
	linkQueue() {front=rear=NULL;}
	~linkQueue();
	bool isEmpty() {return front==NULL;}
	void enQueue(const elemType &x);
	elemType deQueue();
	elemType getHead() {return front->data;}
};

template <class elemType>
void linkQueue<elemType>::enQueue(const elemType &x)
{
	if (rear==NULL)
		front=rear=new node(x);
	else
	{
		rear->next=new node(x);
		rear=rear->next;
	}
}

template <class elemType>
elemType linkQueue<elemType>::deQueue()
{
	node *tmp=front;
	elemType value=front->data;
	front=front->next;
	if (front == NULL) rear=NULL;
	delete tmp;
	return value;
}

template <class elemType>
linkQueue <elemType>::~linkQueue()
{
	node *tmp;
	while (front!=NULL)
	{
		tmp=front;
		front=front->next;
		delete tmp;
	}
}

//链接表图类
template <class TypeOfVer, class TypeOfEdge>
class adjListGraph
{
public:
	adjListGraph(int vSize, const TypeOfVer d[]);	//构造函数(并且完成初始化)
	bool insert(int u, int v, TypeOfEdge w);		//插入
	bool remove(int u, int v);						//删除
	~adjListGraph();                                //析构
	void printPath(int start,int end,int prev[])const;
	void weightedShortDistance(TypeOfVer start,TypeOfEdge noEdge)const;

private:
	struct edgeNode									//边
	{
		int end;
		TypeOfEdge weight;
		edgeNode *next;
		edgeNode(int e, TypeOfEdge w, edgeNode *n=NULL)
		{
			end=e; weight=w; next=n;
		}
	};
	struct verNode									//点
	{
		TypeOfVer ver;
		edgeNode *head;
		verNode(edgeNode *h=NULL)
		{
			head=h;
        }
	};
	verNode *verList;
	int Vers,Edges;
};

//函数实现
//按照书上内容

//构造
template <class TypeOfVer, class TypeOfEdge>
adjListGraph<TypeOfVer, TypeOfEdge>::adjListGraph(int vSize, const TypeOfVer d[])
{
	Vers=vSize; Edges=0;
	verList=new verNode[vSize];
	for (int i=0; i<Vers; i++) verList[i].ver=d[i];
}

//析构
template <class TypeOfVer, class TypeOfEdge>
adjListGraph<TypeOfVer, TypeOfEdge>::~adjListGraph()
{
	int i;
	edgeNode *p;
	for (i=0; i<Vers; i++)
		while ((p=verList[i].head)!=NULL)
		{
			verList[i].head=p->next;
			delete p;
		}
	delete [] verList;
}

//插入边
template <class TypeOfVer, class TypeOfEdge>
bool adjListGraph<TypeOfVer, TypeOfEdge>::insert(int u, int v, TypeOfEdge w)
{
	verList[u].head=new edgeNode(v,w,verList[u].head);
	++Edges;
	return true;
}

//删除边
template <class TypeOfVer, class TypeOfEdge>
bool adjListGraph<TypeOfVer, TypeOfEdge>::remove(int u, int  v)
{
	edgeNode *p=verList[u].head, *q;
	if (p==NULL) return false;
	if (p->end==v)
	{
		verList[u].head=p->next;
		delete p;
		--Edges;
		return true;
	}
	while (p->next!=NULL && p->next->end!=v) p=p->next;
	if (p->next==NULL) return false;
	q=p->next; p->next=q->next; delete q;
	--Edges;
	return true;
}

template <class TypeOfVer,class TypeOfEdge>
void adjListGraph<TypeOfVer,TypeOfEdge>::printPath(int start,int end,int prev[])const
{
    if(start==end){cout<<verList[start].ver;return;}
    printPath(start,prev[end],prev);
    cout<<"-"<<verList[end].ver;
}

template <class TypeOfVer,class TypeOfEdge>
void adjListGraph<TypeOfVer,TypeOfEdge>::weightedShortDistance(TypeOfVer start,TypeOfEdge noEdge)const
{
    linkQueue<int> q;
    TypeOfEdge* distance=new TypeOfEdge[Vers];
    int* prev=new int[Vers];
    int v,sNo,i;
    edgeNode* p;
    for (sNo=0;sNo<Vers;++sNo)  //检查开始点是否存在
    {
        if(verList[sNo].ver==start) break;
        if(sNo==Vers)
        {
            cout<<"起始结点不存在\n";
            return;
        }
    }
    for(i=0;i<Vers;++i)
    {
        distance[i]=noEdge;
    }  //初始化
    distance[sNo]=0;
    prev[sNo]=sNo;
    q.enQueue(sNo);
    while(!q.isEmpty())
    {
        v=q.deQueue();
        for(p=verList[v].head;p!=NULL;p=p->next)  //检查结点v的每一个后继结点
        {
            if(distance[p->end]>distance[v]+p->weight) //找到更好的路径
            {
                distance[p->end]=distance[v]+p->weight;
                prev[p->end]=v;
                q.enQueue(p->end);
            }
        }
    }
    for(i=0;i<Vers;++i)
    {
        cout<<"从"<<start<<"到"<<verList[i].ver<<"的路径为"<<endl;
        printPath(sNo,i,prev);
        cout<<"长度为:"<<distance[i]<<endl;
    }
}

int main()
{
    adjListGraph<char,int>g(7,"0123456");
    g.insert(0,1,2);
    g.insert(0,3,1);
    g.insert(1,3,3);
    g.insert(1,4,10);
    g.insert(2,0,4);
    g.insert(2,5,3);
    g.insert(3,2,2);
    g.insert(3,5,-8);
    g.insert(3,4,2);
    g.insert(3,6,4);
    g.insert(4,6,6);
    g.insert(6,5,1);//按照书本图14-4建图
    g.weightedShortDistance('2',50);
    return 0;
}
