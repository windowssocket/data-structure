#include <iostream>
using namespace std;

template <class elemType>
class stack
{
private:
	struct node	
	{
		elemType data;
		node *next;
		node():next(NULL){}
		node(const elemType &x,node *n=NULL)
		{data=x;next=n;}
		~node(){}
	}; 
	
	node *elem;

public:
	stack()
	{elem = NULL;}
	bool isEmpty()const
	{
		if(elem==NULL) return true;
		else return false;
	}
	void push(const elemType &x)
	{
		node *tmp=new node(x,elem);
		elem=tmp;
	}
	elemType pop()
	{
		node *tmp=elem;
		elemType x=tmp->data;
		elem=elem->next;
		delete tmp;
		return x;
	}
	elemType top()const
	{
		return elem->data;
	}
	~stack();
};

template <class elemType> 
stack <elemType>::~stack()
{
   node *tmp;
   while(elem!=NULL)
   {
	  tmp=elem;
	  elem=elem->next;
	  delete tmp;
   }
}

class Ackerman						
{
private:
	struct Ans{int n1;int n2;int val;} ans;	
	int value;
public:
	Ackerman(int l,int k,int j);
	Ackerman();
	int calc(int m,int n);
};

//主要计算函数calc	利用栈类stack来实现

//分三种情况
//m=0是直接返回
//只有n=0时弹出栈中第一元素,同时压入相等的A(m,n-1)
//m,n都不是0时,压入A(m-1,-1)和A(m,n-1) 其中-1表示这个函数参数未知,等待后一个栈位中的计算结果
//如此往复知道栈中的只有一个元素且其值已经计算出来即可
int Ackerman::calc(int m,int n)
{
	stack<Ackerman> st;
	Ackerman t;
	st.push(Ackerman(m,n,0));
	int final;
	while(!st.isEmpty())
	{
		if(st.top().ans.n1==0)
		{			
			t=st.pop();
			t.ans.val=t.ans.n2+1;
			st.push(t);
			int temp=st.pop().ans.val;
			if (st.isEmpty())
				return temp;
			t=st.pop();
			if (t.ans.val!=-1) t.ans.val=temp;
			else t.ans.n2=temp;
			st.push(t);
			continue;
		}
		else if (st.top().ans.n1!=0&&st.top().ans.n2==0)
		{
			t=st.pop();
			st.push(Ackerman(t.ans.n1-1,1,0));
		}
		else if (st.top().ans.n1!=0&&st.top().ans.n2!=0)
		{
			t=st.pop();
			st.push(Ackerman(t.ans.n1-1,-1,-1));
			st.push(Ackerman(t.ans.n1,t.ans.n2-1,0));
		}
		final=st.top().ans.val;
	}
}

Ackerman::Ackerman()
{
	value=0;
}

Ackerman::Ackerman(int m,int n,int val)
{
	ans.n1=m;
	ans.n2=n;
	ans.val=val;
}

int main()
{
	int m,n;
	cout<<"请输入m的值 m=";
	cin>>m;
	cout<<"请输入n的值 n=";
	cin>>n;
	Ackerman a(m,n,0);
	cout<<"函数的值为: ";
	cout<<a.calc(m,n)<<endl;
	system("pause");
}