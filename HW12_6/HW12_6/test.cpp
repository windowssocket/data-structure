#include<iostream>
#include<fstream>
using namespace std;

struct node{   //�ڽӱ�Ľ����
	int ver;
	node *next;
	node(int x=0,node *p=NULL):ver(x),next(p){}
};

class Queue{  //һ���򵥵Ķ��У���󳤶�Ϊ100
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
	node a[100];  //ʹ���ڽӱ�������ͼ�����ĵ���Ϊ100
	int height[100];  //����ÿ����ĸ߶ȣ���ѧ�ڣ�
	int n,m;
	ifstream fin("test.in");
	ofstream fout("test.out");
	fin>>n>>m;
	for(int i=1; i<=n; ++i) height[i]=1;   //��ʼʱÿ����߶�Ϊ1

	for(int i=0; i<m; ++i){
		int x,y;
		fin>>x>>y;
		a[x].next=new node(y,a[x].next);   //������
		
		Queue Q;
		Q.push(x);
		while(!Q.empty()){
			int tmp=Q.front();
			Q.pop();
			for(node *p=a[tmp].next; p!=NULL; p=p->next){
				if(height[p->ver]<height[tmp]+1){   //�߶�����
					height[p->ver]=height[tmp]+1;
					Q.push(p->ver);
				}
			}
		}
	}

	int maxHeight=1;
	for(int i=1; i<=n; ++i)
		if(height[i]>maxHeight) maxHeight=height[i];   //�ҳ����߶�

	fout<<maxHeight<<endl;

	cout<<"���Խ�����ļ� test.out����"<<endl;
	return 0;
}