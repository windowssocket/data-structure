#include <iostream>
using namespace std;

template <typename Type>
class bernoulli_queue									//贝努利队列类
{
public:
	bernoulli_queue();									//空构造函数
	bernoulli_queue(const bernoulli_queue &x);			//复制构造
	~bernoulli_queue(){};
	void clear()										//清除结点
	{
		for (int i=0; i<currentsize; ++i)
			if (que[i]!=NULL) clear(que[i]);
		delete[] que;
	};
	bool empty() const									 //判空
	{
		for (int i=0; i<currentsize; ++i)
			if (que[i]==NULL) return false;
		return true;
	};
	int size() const;									//判断队列大小
	const Type& top() const;							//得到首元素
	void pop();											//弹出首元素(最小元素)
	void push(const Type&);
	bernoulli_queue operator +(const bernoulli_queue &x);//重载加法
	bernoulli_queue& operator =(const bernoulli_queue &x) //重载赋值 利用复制函数
	{
		for (int i=0; i<x.currentsize; ++i)
		{
			if (x.que[i]==NULL)
			{
				que[i]=NULL;
				continue;
			}
			que[i]=copytree(x.que[i]);
		}
		currentsize=x.currentsize;
		return *this;
	};
private:
	struct treenode				//儿子兄弟树节点类
	{
		treenode *son,*brother;
		Type data;
		treenode():son(NULL),brother(NULL){};
		treenode(Type x, treenode *s=NULL, treenode *b=NULL):data(x),son(s),brother(b){};
		~treenode(){};
	};
	treenode **que;				//存有根结点的指针队列
	int maxsize;
	int currentsize;
	void doublespace();			//增加空间
	void clear(treenode *t);
	treenode* copytree(treenode *t)			//复制一棵完整的树
	{
		treenode *p=new treenode;
		p->data=t->data;
		p->son=NULL; p->brother=NULL;
		if (t->son != NULL) p->son=copytree(t->son);
		if (t->brother != NULL) p->brother=copytree(t->brother);
		return p;
	}
	treenode* connect(treenode *x, treenode *y)				//将y为根的树连到x为根的树上
	{
		treenode *tmp=x;
		if (x->son == NULL)
		{
			x->son=y;
			return tmp;
		}
		else
		{
			x=x->son;
			while (x->brother!=NULL) x=x->brother;
			x->brother=y;
			return tmp;
		}
	}
};

//以上函数的实现
template <class Type>
bernoulli_queue<Type>::bernoulli_queue()
{
	maxsize=400;
	que=new treenode*[maxsize];
	for (int i=0; i<maxsize; ++i)
		que[i]=NULL;
	currentsize=0;
}

template <class Type>
bernoulli_queue<Type>::bernoulli_queue(const bernoulli_queue &x)
{
	maxsize=400;
	que=new treenode*[maxsize];
	for (int i=0; i<maxsize; ++i)
		que[i]=NULL;
	currentsize=0;
	for (int i=0; i<x.currentsize; ++i)
	{
		if (x.que[i]==NULL)
		{
			que[i]=NULL;
			continue;
		}
		que[i]=copytree(x.que[i]);
	}
	currentsize=x.currentsize;
}

template <class Type>
void bernoulli_queue<Type>::doublespace()
{
	treenode **tmp=que;
	maxsize*=2;
	que=new treenode*[maxsize];
	for (int i=0; i<maxsize; ++i)
		que[i]=NULL;
	for (int i=0; i<currentsize; ++i)
		que[i]=tmp[i];
	delete [] tmp;
}

template <class Type>
int bernoulli_queue<Type>::size() const
{
	int ans=0;
	for (int i=0; i<currentsize; ++i)
		ans+=((i+1) << i);							//位移运算实现2的阶乘
	return ans;
}

template <class Type>
const Type& bernoulli_queue<Type>::top() const
{
	bool firsttime=true;
	Type min;
	for (int i=0; i<currentsize; ++i)
		if (que[i]!=NULL)
		{
			if (firsttime)
			{
				min=que[i]->data;
				firsttime=false;
			}
			else if (que[i]->data<min)  min=que[i]->data;
		}
	return min;
}

template <class Type>
void bernoulli_queue<Type>::pop()
{
	bernoulli_queue<Type> tmp(*this);
	bool firsttime=true;
	Type min;
	int num=0,i;
	for (i=0; i<currentsize; ++i)					//寻找最小点
		if (que[i]!=NULL)
		{
			if (firsttime)
			{
				firsttime=false;
				min=que[i]->data;
				num=i;
			}
			else
			{
				if (que[i]->data<min)
				{
					min=que[i]->data;
					num=i;
				}
			}
		}
	treenode *last=que[num]->son;
	i=0;
	while (last!=NULL)				//合并剩下的残支组成一个新的队列
	{
		tmp.que[i]=last;
		last=last->brother;
		tmp.que[i]->brother=NULL;
		i++;
	}
	tmp.currentsize=i;
	delete que[num];
	que[num]=NULL;
	*this=*this+tmp;
}

template <class Type>
void bernoulli_queue<Type>::push (const Type& value)	//新建一个结点然后把它压入队中
{
	treenode *tmp=new treenode(value),*t;
	int i=0;
	while (que[i]!=NULL)
	{
		if (tmp->data > que[i]->data)
		{ t=que[i]; que[i]=tmp; tmp=t;}
		tmp=connect(tmp,que[i]);
		que[i]=NULL;
		i++;
		if (i == maxsize) doublespace();
	}
	que[i]=tmp;
	if (i >= currentsize) currentsize=i+1;
}

template <class Type>
void bernoulli_queue<Type>::clear (treenode *t)
{
	if (t->son != NULL) clear(t->son);
	if (t->brother != NULL) clear(t->brother);
	delete t;
}

template <class Type>
bernoulli_queue<Type> bernoulli_queue<Type>::operator +(const bernoulli_queue<Type> &A)
{
	bernoulli_queue<Type> tmp(A);
	bernoulli_queue<Type> ans(*this);
	treenode *carryin=NULL,*carryout=NULL;       //用于记下进位,类似于数电..
	treenode *t;
	int maxLength;
	if (currentsize > tmp.currentsize) maxLength=currentsize;
	else maxLength=tmp.currentsize;
	int i;
	for (i=0; i<maxLength; i++)
	{
		//分三种情况进行加法
		if ((ans.que[i]!=NULL) && (tmp.que[i]!=NULL))
		{
			if (ans.que[i]->data > tmp.que[i]->data)
			{ t=ans.que[i]; ans.que[i]=tmp.que[i]; tmp.que[i]=t; }
			carryout=connect(ans.que[i],tmp.que[i]);
			ans.que[i]=carryin;
		}
		else if ((ans.que[i] == NULL) && (tmp.que[i] != NULL))
		{
			ans.que[i]=tmp.que[i];
			if (carryin != NULL)
			{
				if (ans.que[i]->data > carryin->data)
				{ t=ans.que[i]; ans.que[i]=carryin; carryin=t;}
				carryout=connect(ans.que[i],carryin);
				ans.que[i]=NULL;
			}
		}
		else if ((ans.que[i] == NULL) && (tmp.que[i] == NULL))
		{
			ans.que[i]=carryin;
		}
		carryin=carryout;//下次的加法的进位是这次算到的
		carryout=NULL;//赋空
	}
	if (carryin != NULL)//处理最后一个位上是否有进位
		{ans.que[i]=carryin; carryin=NULL; ans.currentsize=maxLength+1;}
	else {ans.currentsize=maxLength;}
	tmp.~bernoulli_queue();
	return bernoulli_queue(ans);//利用复制构造函数来返回
}

//简单的测试
int main()
{
	int a;
	bernoulli_queue<int> que1,que2,que3;
	for (int i=1; i<=10; i++)					//10 -> 1
		que1.push(10-i+1);
	for (int i=1; i<=10; i++)					//1 -> 10
		que2.push(i);
	que3=que1+que2;								//合并
	for (int i=1; i<=20; i++)
	{
		a=que3.top();
		cout << que3.top() << ' ';				//输出
		que3.pop();
	}
}
