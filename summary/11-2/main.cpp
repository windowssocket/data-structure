#include <iostream>
#include <time.h>
#include <stdlib.h>
using namespace std;

static bool check(int n,int row,int column)  //判断起点、终点是否超出迷宫范围
{
    if(row>n||column>n) return false;
    if(column==1||row==column||row==n) return true;
    return false;
}

//按书上
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
    while(!flag)  //如果输入的入口的行号、入口的列号、出口的行号、出口的列号非法，则重新输入
    {
        if(!check(n,startrow,startcolumn) || !check(n,endrow,endcolumn)){
            cout<<"非法的入口或者出口\n";
            cout<<"请依次再次输入，入口的行号、入口的列号、出口的行号、出口的列号：";
            cin>>startrow;
            cin>>startcolumn;
            cin>>endrow;
            cin>>endcolumn;
        }
        else flag=1;
    }
    int size=n*(n+1)/2;  //计算不相交集的大小
    int row,column,num1,num2;
    int start=startrow*(startrow-1)/2+startcolumn-1;  //计算入口编号(编号是从0开始的)
    int end=endrow*(endrow-1)/2+endcolumn-1;    //计算出口编号

    DisjointSet ds(size);   //size为迷宫规模
    srand(time(NULL));
    while(ds.Find(start)!=ds.Find(end))   //入口和出口不连通，则循环
    {
        while(true){
        row=rand()*n/(RAND_MAX+1)+1;   //随机生成行号
        column=rand()*row/(RAND_MAX+1)+1;   //随机生成列号
        num1=row*(row-1)/2+column-1;    //计算随机单元的编号
        if(row!=1)   //不是第一行的单元情况
        {
            if(column>1)     //不是最左边的单元，检查左上角
            {
                num2=(row-2)*(row-1)/2+column-2;
                if(ds.Find(num1)!=ds.Find(num2)) break;
            }
            if(column<row)     //不是最右边的单元，检查右上角
            {
                num2=(row-1)*(row-2)/2+column-1;
                if(ds.Find(num1)!=ds.Find(num2)) break;
            }
        }
        if(column>1)    //不是最左边的单元，检查左边相邻单元
        {
            num2=num1-1;
            if(ds.Find(num1)!=ds.Find(num2)) break;
        }
        if(column<row)   //不是最右边的单元，检查右边相邻单元
        {
            num2=num1+1;
            if(ds.Find(num1)!=ds.Find(num2)) break;
        }
        if(row<n)    //不是最后一行的单元，检查下边相邻两个单元
        {
            num2=(row+1)*row/2+column-1;
            if(ds.Find(num1)!=ds.Find(num2)) break;
            ++num2;
            if(ds.Find(num1)!=ds.Find(num2)) break;
        }
        }
        ds.Union(ds.Find(num1),ds.Find(num2));    //连通num1和num2
        cout<<"<"<<num1<<","<<num2<<">,";
    }
}

int main()
{
    createPuzzle(5,1,1,5,5);  //一共五行，起点为第一行第一列，终点为第五行第五列
}
