#include <iostream>
using namespace std;

template<class TypeOfVer,class TypeOfEdge>

class adjListGraph
{
public:
  adjListGraph(int vsize,const TypeOfVer d[]);
  bool insert(int u,int v,TypeOfEdge w);
  bool remove(int u,int v);
  bool exist(int u,int v)const;
  void find(TypeOfVer start,int M)
  {
    int st;//������ʼ����
    temp=new int[M];
    size=M;
    visited=new bool[Vers];
    for(int i=0;i<Vers;i++)
    {
        visited[i]=false;
        if(verList[i].ver==start)
        st=i;
    }
    find(st,M);
  }
  void find(int start,int M);
  ~adjListGraph();

private:
struct edgeNode{
        int end;
        TypeOfEdge weight;
        edgeNode* next;
        edgeNode(int e,TypeOfEdge w,edgeNode* n=NULL)
        {end=e;weight=w;next=n;}
};
struct verNode{
        TypeOfVer ver;
        edgeNode* head;
        verNode(edgeNode* h=NULL)
        {head=h;}
};
verNode* verList;
int Vers,Edges;
int *temp;
int size;
bool* visited;
};

//������������
template<class TypeOfVer,class TypeOfEdge>
adjListGraph<TypeOfVer,TypeOfEdge>::adjListGraph(int vSize,const TypeOfVer d[])
{
  Vers=vSize;Edges=0;
  verList=new verNode[vSize];
  for(int i=0;i<vSize;i++) verList[i].ver=d[i];
}

template<class TypeOfVer,class TypeOfEdge>
adjListGraph<TypeOfVer,TypeOfEdge>::~adjListGraph()
{
    int i;
    edgeNode* p;
    for(i=0;i<Vers;i++)
    while((p=verList[i].head)!=NULL){
    verList[i].head=p->next;
    delete p;
    }
    delete[] verList;
}

template<class TypeOfVer,class TypeOfEdge>
bool adjListGraph<TypeOfVer,TypeOfEdge>::insert(int u,int v,TypeOfEdge w)
{
    verList[u].head=new edgeNode(v,w,verList[u].head);
    ++Edges;
    return true;
}

template<class TypeOfVer,class TypeOfEdge>
bool adjListGraph<TypeOfVer,TypeOfEdge>::remove(int u,int v)
{
    edgeNode* p=verList[u].head,*q;
    if(p==NULL) return false;
    if(p->end==v)
    {
        verList[u].head=p->next;
        delete p;--Edges;
        return true;
    }
    while(p->next!=NULL&&p->next->end!=v) p=p->next;
    if(p->next==NULL) return false;
    q=p->next;
    p->next=q->next;
    delete q;
    --Edges;
    return true;
}

template<class TypeOfVer,class TypeOfEdge>
bool adjListGraph<TypeOfVer,TypeOfEdge>::exist(int u,int v)const
{
  edgeNode* p=verList[u].head;
  while(p!=NULL)
  {
      if(p->end==u)
      return true;
      p=p->next;
  }
  return false;
}

//Ѱ��·������ΪM��·�������õݹ�˼��
template<class TypeOfVer,class TypeOfEdge>
void adjListGraph<TypeOfVer,TypeOfEdge>::find(int start,int M)
{
    edgeNode* p=verList[start].head;
    if(M==0) {cout<<"û�н��"<<endl;return;} //·������Ϊ0�����
    if(M==1) {cout<<verList[start].ver<<'\t';return;} //·������Ϊ1�����
    if(M==2)
    {
        temp[size-2]=start;
        visited[temp[0]]=false;
        while(p!=NULL)
        {
            if(visited[p->end]==false) temp[size-1]=p->end;
            for(int i=0;i<size;i++) cout<<verList[temp[i]].ver<<'\t';
            cout<<endl;
            p=p->next;
        }
        return;
    }
    visited[start]=true;
    temp[size-M]=start;
    while(p!=NULL)
    {
        if(visited[p->end]==false) find(p->end,M-1);
        visited[p->end]=false; p=p->next;
    }
}

int main()
{
    //cout<<"�鱾361ҳ��ͼ"<<endl;
    //string a[7]={"��ѧ","�������","��ɢ��ѧ","�������","���ݽṹ","���ݿ�","����ԭ��"};
    //adjListGraph<string,int>  g(7,a);
    //g.insert(0,1,9);
    //g.insert(0,2,9);
    //g.insert(2,6,9);
    //g.insert(2,4,9);
    //g.insert(4,6,9);
    //g.insert(1,3,9);
   // g.insert(1,4,9);
   // g.insert(1,5,9);
   // g.insert(4,5,9);
   // g.insert(5,3,9);
    //g.insert(3,0,9);
   // g.find("��ѧ",4);
    adjListGraph<char,int> m(7,"1234567");
	m.insert(0,1,1);
	m.insert(1,2,1);
	m.insert(1,3,1);
	m.insert(2,0,1);
	m.insert(3,2,1);
	m.insert(3,0,1);
	m.insert(4,5,1);
	m.insert(4,6,1);
	m.insert(5,1,1);
	m.insert(6,5,1);
	m.insert(6,3,1);
	m.find('4',4);
    return 0;
}
