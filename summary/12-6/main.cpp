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
	void Findterm();

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

template <class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::Findterm()
{
    linkQueue<int> q1,q2;
    edgeNode *p;
    int i;
    int current,term=1;
    int *inDegree=new int[Vers];
    for(i=0;i<Vers;++i) inDegree[i]=0;
    for(i=0;i<Vers;++i)     //����������
       for(p=verList[i].head;p!=NULL;p=p->next)
           ++inDegree[p->end];
    for(i=0;i<Vers;++i)     //�����Ϊ0�Ľ�����q1
       if(inDegree[i]==0) q1.enQueue(i);
    cout<<"�γ̰���Ϊ:";
    while(1)
    {
        cout<<"\n��"<<term<<"ѧ�ڵĿγ�Ϊ:";
        while(!q1.isEmpty())
        {
            current=q1.deQueue();
            cout<<verList[current].ver<<" ";
            for(p=verList[current].head;p!=NULL;p=p->next)
                if(--inDegree[p->end]==0) q2.enQueue(p->end);  //���¸�ѧ�ڵĿγ̴���q2��
        }
        if(q2.isEmpty())break;    //�����ѧ�ڵĿγ�Ϊ��,�����ѭ��
        ++term;
        cout<<"\n��"<<term<<"ѧ�ڵĿγ�Ϊ:";
        while(!q2.isEmpty())
        {
            current=q2.deQueue();
            cout<<verList[current].ver<<" ";
            for(p=verList[current].head;p!=NULL;p=p->next)
                if(--inDegree[p->end]==0) q1.enQueue(p->end);  //���¸�ѧ�ڵĿγ̴���q1��
        }
        if(q1.isEmpty()) break;    //�����ѧ�ڵĿγ�Ϊ��,�����ѭ��
        ++term;
    }
    cout<<"\n"<<"���ٻ�"<<term<<"��ѧ������ȫ���γ�\n";
}

//���Գ���
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
    g.insert(5,3,1);  //�����鱾ͼ12-15��ͼ
    g.Findterm();
}
