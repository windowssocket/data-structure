#include <iostream>

using namespace std;

//���������
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

//���ӱ�ͼ��
template <class TypeOfVer, class TypeOfEdge>
class adjListGraph
{
public:
	adjListGraph(int vSize, const TypeOfVer d[]);	//���캯��(������ɳ�ʼ��)
	bool insert(int u, int v, TypeOfEdge w);		//����
	bool remove(int u, int v);						//ɾ��
	~adjListGraph();                                //����
	void printPath(int start,int end,int prev[])const;
	void weightedShortDistance(TypeOfVer start,TypeOfEdge noEdge)const;

private:
	struct edgeNode									//��
	{
		int end;
		TypeOfEdge weight;
		edgeNode *next;
		edgeNode(int e, TypeOfEdge w, edgeNode *n=NULL)
		{
			end=e; weight=w; next=n;
		}
	};
	struct verNode									//��
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

//����ʵ��
//������������

//����
template <class TypeOfVer, class TypeOfEdge>
adjListGraph<TypeOfVer, TypeOfEdge>::adjListGraph(int vSize, const TypeOfVer d[])
{
	Vers=vSize; Edges=0;
	verList=new verNode[vSize];
	for (int i=0; i<Vers; i++) verList[i].ver=d[i];
}

//����
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

//�����
template <class TypeOfVer, class TypeOfEdge>
bool adjListGraph<TypeOfVer, TypeOfEdge>::insert(int u, int v, TypeOfEdge w)
{
	verList[u].head=new edgeNode(v,w,verList[u].head);
	++Edges;
	return true;
}

//ɾ����
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
    for (sNo=0;sNo<Vers;++sNo)  //��鿪ʼ���Ƿ����
    {
        if(verList[sNo].ver==start) break;
        if(sNo==Vers)
        {
            cout<<"��ʼ��㲻����\n";
            return;
        }
    }
    for(i=0;i<Vers;++i)
    {
        distance[i]=noEdge;
    }  //��ʼ��
    distance[sNo]=0;
    prev[sNo]=sNo;
    q.enQueue(sNo);
    while(!q.isEmpty())
    {
        v=q.deQueue();
        for(p=verList[v].head;p!=NULL;p=p->next)  //�����v��ÿһ����̽��
        {
            if(distance[p->end]>distance[v]+p->weight) //�ҵ����õ�·��
            {
                distance[p->end]=distance[v]+p->weight;
                prev[p->end]=v;
                q.enQueue(p->end);
            }
        }
    }
    for(i=0;i<Vers;++i)
    {
        cout<<"��"<<start<<"��"<<verList[i].ver<<"��·��Ϊ"<<endl;
        printPath(sNo,i,prev);
        cout<<"����Ϊ:"<<distance[i]<<endl;
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
    g.insert(6,5,1);//�����鱾ͼ14-4��ͼ
    g.weightedShortDistance('2',50);
    return 0;
}
