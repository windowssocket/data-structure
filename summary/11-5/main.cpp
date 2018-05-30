#include <iostream>

using namespace std;

//���ཻ����
class DisjointSet{
private:
      int size;
      int* parent;

public:
      DisjointSet(int s);
      ~DisjointSet(){delete [] parent;}
      void Union(int root1,int root2);
      int Find(int x);
      int Getparent(int y){return parent[y];}
};

DisjointSet::DisjointSet(int n)
{
    size=n;
    parent=new int[size];
    for(int i=0;i<size;i++) parent[i]=-1;
}

int DisjointSet::Find(int x)
{
    int front=x;
    int tmp;
    while(parent[x]>=0)
    {
        x=parent[x];
    }    //Ѱ�Ҹ��ڵ�
    while(front!=x)
    {
        tmp=parent[front];
        parent[front]=x;
        front=tmp;
    }    //·��ѹ��
    return x;
}

void DisjointSet::Union(int root1,int root2)
{
    if(root1==root2) return;
    if(parent[root1]>parent[root2])
    {
        parent[root2]+=parent[root1];parent[root1]=root2;
    }
    else{parent[root1]+=parent[root2];parent[root2]=root1;}
}

int main()
{
    DisjointSet list(15);
    list.Union(0,1);
    list.Union(0,2);
    list.Union(0,3);
    list.Union(4,5);
    list.Union(6,7);
    list.Union(6,8);
    list.Union(9,10);
    list.Union(11,12);
    list.Union(9,11);
    cout<<"12��parent��"<<list.Getparent(12)<<endl;
    cout<<"12���ڵ��Ӽ���"<<list.Find(12)<<endl;
    cout<<"����Find��12��������12��parent��"<<list.Getparent(12)<<endl;
    return 0;
}
