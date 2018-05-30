#include <iostream>
#include <time.h>
#include <stdlib.h>
using namespace std;

static bool check(int n,int row,int column)  //�ж���㡢�յ��Ƿ񳬳��Թ���Χ
{
    if(row>n||column>n) return false;
    if(column==1||row==column||row==n) return true;
    return false;
}

//������
class DisjointSet{
private:
      int size;
      int* parent;

public:
      DisjointSet(int s);
      ~DisjointSet(){delete [] parent;}
      void Union(int root1,int root2);
      int Find(int x);
};

DisjointSet::DisjointSet(int n)
{
    size=n;
    parent=new int[size];
    for(int i=0;i<size;i++) parent[i]=-1;
}

int DisjointSet::Find(int x)
{
    if(parent[x]<0) return x;
    return parent[x]=Find(parent[x]);
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

void createPuzzle(int n,int startrow,int startcolumn,int endrow,int endcolumn)
{
    int flag=0;
    while(!flag)  //����������ڵ��кš���ڵ��кš����ڵ��кš����ڵ��кŷǷ�������������
    {
        if(!check(n,startrow,startcolumn) || !check(n,endrow,endcolumn)){
            cout<<"�Ƿ�����ڻ��߳���\n";
            cout<<"�������ٴ����룬��ڵ��кš���ڵ��кš����ڵ��кš����ڵ��кţ�";
            cin>>startrow;
            cin>>startcolumn;
            cin>>endrow;
            cin>>endcolumn;
        }
        else flag=1;
    }
    int size=n*(n+1)/2;  //���㲻�ཻ���Ĵ�С
    int row,column,num1,num2;
    int start=startrow*(startrow-1)/2+startcolumn-1;  //������ڱ��(����Ǵ�0��ʼ��)
    int end=endrow*(endrow-1)/2+endcolumn-1;    //������ڱ��

    DisjointSet ds(size);   //sizeΪ�Թ���ģ
    srand(time(NULL));
    while(ds.Find(start)!=ds.Find(end))   //��ںͳ��ڲ���ͨ����ѭ��
    {
        while(true){
        row=rand()*n/(RAND_MAX+1)+1;   //��������к�
        column=rand()*row/(RAND_MAX+1)+1;   //��������к�
        num1=row*(row-1)/2+column-1;    //���������Ԫ�ı��
        if(row!=1)   //���ǵ�һ�еĵ�Ԫ���
        {
            if(column>1)     //��������ߵĵ�Ԫ��������Ͻ�
            {
                num2=(row-2)*(row-1)/2+column-2;
                if(ds.Find(num1)!=ds.Find(num2)) break;
            }
            if(column<row)     //�������ұߵĵ�Ԫ��������Ͻ�
            {
                num2=(row-1)*(row-2)/2+column-1;
                if(ds.Find(num1)!=ds.Find(num2)) break;
            }
        }
        if(column>1)    //��������ߵĵ�Ԫ�����������ڵ�Ԫ
        {
            num2=num1-1;
            if(ds.Find(num1)!=ds.Find(num2)) break;
        }
        if(column<row)   //�������ұߵĵ�Ԫ������ұ����ڵ�Ԫ
        {
            num2=num1+1;
            if(ds.Find(num1)!=ds.Find(num2)) break;
        }
        if(row<n)    //�������һ�еĵ�Ԫ������±�����������Ԫ
        {
            num2=(row+1)*row/2+column-1;
            if(ds.Find(num1)!=ds.Find(num2)) break;
            ++num2;
            if(ds.Find(num1)!=ds.Find(num2)) break;
        }
        }
        ds.Union(ds.Find(num1),ds.Find(num2));    //��ͨnum1��num2
        cout<<"<"<<num1<<","<<num2<<">,";
    }
}

int main()
{
    createPuzzle(5,1,1,5,5);  //һ�����У����Ϊ��һ�е�һ�У��յ�Ϊ�����е�����
}
