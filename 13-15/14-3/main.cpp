#include <iostream>

using namespace std;

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
	void dijkstra(TypeOfVer start,TypeOfEdge noEdge)const;
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
void adjListGraph<TypeOfVer,TypeOfEdge>::dijkstra(TypeOfVer start,TypeOfEdge noEdge)const
{
    TypeOfEdge* distance=new TypeOfEdge[Vers];
    int* prev=new int[Vers];
    int* number=new int[Vers]; //记录经过的结点数
    bool* known=new bool[Vers];
    int u,sNo,i,j;
    edgeNode* p;
    TypeOfEdge min;
    for (sNo=0;sNo<Vers;++sNo)  //检查开始结点是否存在
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
        known[i]=false;
        number[i]=0;
    }  //初始化
    distance[sNo]=0;
    prev[sNo]=sNo;
    for(i=1;i<Vers;++i)   //寻找Vers-1个结点的最短路径
    {
        min=noEdge;
        for(j=0;j<Vers;++j)
        {
            if(!known[j]&&distance[j]<min)
            {
                min=distance[j];
                u=j;
            }
        }
        known[u]=true;
        for(p=verList[u].head;p!=NULL;p=p->next)
        {
            if((!known[p->end])&&((distance[p->end]>min+p->weight)||(distance[p->end]==min+p->weight&&number[p->end]>number[u]+1)))
            {
                distance[p->end]=min+p->weight;
                number[p->end]=number[u]+1;
                prev[p->end]=u;
            }
        }
    }
    for(i=0;i<Vers;++i)  //输出最短路径
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
    g.insert(2,5,5);
    g.insert(3,2,2);
    g.insert(3,5,8);
    g.insert(3,4,2);
    g.insert(3,6,4);
    g.insert(4,6,6);
    g.insert(6,5,1);//按照书本图14-2建图
    g.dijkstra('1',50);
    return 0;
}
