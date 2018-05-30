#include<iostream>
#include<fstream>
using namespace std;

struct node{   //邻接表的结点类
	int ver;
	node *next;
	node(int x=0,node *p=NULL):ver(x),next(p){}
};

class Queue{  //一个简单的队列，最大长度为100
private:
	int data[100];
	int head,tail;
	void next(int &x){if(++x==100) x=0;}
public:
	Queue():head(0),tail(0){}
	int front(){return data[head];}
	bool empty(){return head==tail;}
	void pop(){next(head);}
	void push(int x){data[tail]=x;next(tail);}
};

int main()
{
	node a[100];  //使用邻接表来保存图，最大的点数为100
	int height[100];  //保存每个点的高度（即学期）
	int n,m;
	ifstream fin("test.in");
	ofstream fout("test.out");
	fin>>n>>m;
	for(int i=1; i<=n; ++i) height[i]=1;   //初始时每个点高度为1

	for(int i=0; i<m; ++i){
		int x,y;
		fin>>x>>y;
		a[x].next=new node(y,a[x].next);   //插入结点
		
		Queue Q;
		Q.push(x);
		while(!Q.empty()){
			int tmp=Q.front();
			Q.pop();
			for(node *p=a[tmp].next; p!=NULL; p=p->next){
				if(height[p->ver]<height[tmp]+1){   //高度增加
					height[p->ver]=height[tmp]+1;
					Q.push(p->ver);
				}
			}
		}
	}

	int maxHeight=1;
	for(int i=1; i<=n; ++i)
		if(height[i]>maxHeight) maxHeight=height[i];   //找出最大高度

	fout<<maxHeight<<endl;

	cout<<"测试结果在文件 test.out里面"<<endl;
	return 0;
}