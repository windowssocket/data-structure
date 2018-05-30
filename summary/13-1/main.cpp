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
	void prim(TypeOfEdge noEdge)const;

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


template<class TypeOfVer,class TypeOfEdge>
void adjListGraph<TypeOfVer,TypeOfEdge>::prim(TypeOfEdge noEdge)const
{
    bool* flag=new bool[Vers];
    int* startNode=new int[Vers];
    TypeOfEdge* lowCost=new TypeOfEdge[Vers];

    edgeNode* p;
    TypeOfEdge min;
    int start,i,j;

    for(i=0;i<Vers;++i)
    {
        flag[i]=false;
        lowCost[i]=noEdge;
    }//初始化，所有节点都不在生成树中

    while(1){
    cout<<"请输入起始点：";
    cin>>start;
    if(start>=0&&start<Vers) break;
    cout<<"没有这个点\n";
    }
    for(i=1;i<Vers;++i)
    {
        for(p=verList[start].head;p!=NULL;p=p->next){
            if(!flag[p->end]&&lowCost[p->end]>p->weight){
                lowCost[p->end]=p->weight;
                startNode[p->end]=start;
            }
        }
        flag[start]=true;
        min=noEdge;
        for(j=0;j<Vers;++j){
            if(lowCost[j]<min){min=lowCost[j];start=j;}
        }
        cout<<'('<<verList[startNode[start]].ver<<','<<verList[start].ver<<")\t";
        lowCost[start]=noEdge;
    }
    delete [] flag;
    delete [] startNode;
    delete [] lowCost;
}

int main()
{
    adjListGraph<char,int>g(6,"123456");
    g.insert(0,1,6);
    g.insert(0,3,5);
    g.insert(0,2,1);
    g.insert(1,2,5);
    g.insert(1,4,3);
    g.insert(2,3,5);
    g.insert(2,4,6);
    g.insert(2,5,4);
    g.insert(3,5,2);
    g.insert(4,5,6);
    g.insert(1,0,6);
    g.insert(3,0,5);
    g.insert(2,0,1);
    g.insert(2,1,5);
    g.insert(4,1,3);
    g.insert(3,2,5);
    g.insert(4,2,6);
    g.insert(5,2,4);
    g.insert(5,3,2);
    g.insert(5,4,6);
    g.prim(100);
}
