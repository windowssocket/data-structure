#include <iostream>

using namespace std;

template <class Type>
class priorityQueue
{
public:
	priorityQueue(int capacity=100)//���캯��
	{
		data=new Type[capacity];
		maxSize=capacity;
		currentSize=0;
	}
	priorityQueue(const Type data[], int size);//���ƹ���
	~priorityQueue() {delete []data; }
	bool isEmpty() const {return currentSize==0;}//�п�
	void enQueue(Type x);//���
	Type deQueue();//����
	Type getHead() const {return data[1];}//�õ��׽ڵ�
private:
	int currentSize;
	Type *data;
	int maxSize;

	void doubleSpace();
	void buildHeap();
	void percolateDown(int hole);
};

//����ʵ��
template <class Type>
void priorityQueue<Type>::enQueue(Type x)
{
	if (currentSize==maxSize-1) doubleSpace();
	int hole=++currentSize;
	while (hole>1 && x<data[hole/2])
	{
		data[hole]=data[hole/2];
		hole=hole/2;
	}
	data[hole]=x;
}

template <class Type>
Type priorityQueue<Type>::deQueue()
{
	Type minItem=data[1];
	data[1]=data[currentSize--];
	percolateDown(1);
	return minItem;
}

template <class Type>
void priorityQueue<Type>::percolateDown(int hole)
{
	int child;
	Type tmp=data[hole];
	while (hole*2<=currentSize)
	{
		child=hole*2;
		if (child!=currentSize && data[child+1]<data[child]) child++;
		if (data[child]<tmp) data[hole]=data[child];
		    else break;
		hole=child;
	}
	data[hole]=tmp;
}

template <class Type>
void priorityQueue<Type>::buildHeap()
{
	for (int i=currentSize/2; i>0; i--)
		percolateDown(i);
}

template <class Type>
void priorityQueue<Type>::doubleSpace()
{
	Type *tmp=data;
	maxSize*=2;
	data=new Type[maxSize];
	for (int i=0; i<=currentSize; i++) data[i]=tmp[i];
	delete []tmp;
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
	void dijkstra(TypeOfVer start,TypeOfEdge noEdge)const;
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
	struct queuenode
    {
        TypeOfEdge dist;
        int node;

        bool operator<(const queuenode &r)const{return dist<r.dist;}
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
void adjListGraph<TypeOfVer,TypeOfEdge>::dijkstra(TypeOfVer start,TypeOfEdge noEdge)const
{
    TypeOfEdge* distance=new TypeOfEdge[Vers];
    int* prev=new int[Vers];
    bool* known=new bool[Vers];
    int sNo,i;
    edgeNode* p;
    priorityQueue <queuenode> q;
    queuenode min,s;
    for (sNo=0;sNo<Vers;++sNo)  //��鿪ʼ����Ƿ����
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
        known[i]=false;
    }  //��ʼ��
    distance[sNo]=0;
    prev[sNo]=sNo;
    min.dist=0;
    min.node=sNo;
    q.enQueue(min);
    while(!q.isEmpty())
    {
        min=q.deQueue();
        if(known[min.node])continue;
        known[min.node]=true;
        for(p=verList[min.node].head;p!=NULL;p=p->next)
        {
            if(!known[p->end]&&distance[p->end]>min.dist+p->weight)
            {
                distance[p->end]=min.dist+p->weight;
                s.dist=distance[p->end];
                prev[p->end]=min.node;
                s.node=p->end;
                q.enQueue(s);
            }
        }
    }
    for(i=0;i<Vers;++i)  //������·��
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
    g.insert(2,5,5);
    g.insert(3,2,2);
    g.insert(3,5,8);
    g.insert(3,4,2);
    g.insert(3,6,4);
    g.insert(4,6,6);
    g.insert(6,5,1);//�����鱾ͼ14-2��ͼ
    g.dijkstra('1',50);
    return 0;
}
