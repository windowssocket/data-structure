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
	void Findterm();

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

template <class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::Findterm()
{
    linkQueue<int> q1,q2;
    edgeNode *p;
    int i;
    int current,term=1;
    int *inDegree=new int[Vers];
    for(i=0;i<Vers;++i) inDegree[i]=0;
    for(i=0;i<Vers;++i)     //计算结点的入度
       for(p=verList[i].head;p!=NULL;p=p->next)
           ++inDegree[p->end];
    for(i=0;i<Vers;++i)     //将入度为0的结点放入q1
       if(inDegree[i]==0) q1.enQueue(i);
    cout<<"课程安排为:";
    while(1)
    {
        cout<<"\n第"<<term<<"学期的课程为:";
        while(!q1.isEmpty())
        {
            current=q1.deQueue();
            cout<<verList[current].ver<<" ";
            for(p=verList[current].head;p!=NULL;p=p->next)
                if(--inDegree[p->end]==0) q2.enQueue(p->end);  //把下个学期的课程存在q2中
        }
        if(q2.isEmpty())break;    //如果下学期的课程为空,则结束循环
        ++term;
        cout<<"\n第"<<term<<"学期的课程为:";
        while(!q2.isEmpty())
        {
            current=q2.deQueue();
            cout<<verList[current].ver<<" ";
            for(p=verList[current].head;p!=NULL;p=p->next)
                if(--inDegree[p->end]==0) q1.enQueue(p->end);  //把下个学期的课程存在q1中
        }
        if(q1.isEmpty()) break;    //如果下学期的课程为空,则结束循环
        ++term;
    }
    cout<<"\n"<<"最少花"<<term<<"个学期修完全部课程\n";
}

//测试程序
int main()
{
    adjListGraph<char,int>g(7,"1234567");
    g.insert(0,2,1);
    g.insert(0,1,1);
    g.insert(2,6,1);
    g.insert(2,4,1);
    g.insert(1,4,1);
    g.insert(1,5,1);
    g.insert(1,3,1);
    g.insert(4,6,1);
    g.insert(4,5,1);
    g.insert(5,3,1);  //按照书本图12-15建图
    g.Findterm();
}
