#include <iostream>
using namespace std;

template <typename Type>
class bernoulli_queue									//��Ŭ��������
{
public:
	bernoulli_queue();									//�չ��캯��
	bernoulli_queue(const bernoulli_queue &x);			//���ƹ���
	~bernoulli_queue(){};
	void clear()										//������
	{
		for (int i=0; i<currentsize; ++i)
			if (que[i]!=NULL) clear(que[i]);
		delete[] que;
	};
	bool empty() const									 //�п�
	{
		for (int i=0; i<currentsize; ++i)
			if (que[i]==NULL) return false;
		return true;
	};
	int size() const;									//�ж϶��д�С
	const Type& top() const;							//�õ���Ԫ��
	void pop();											//������Ԫ��(��СԪ��)
	void push(const Type&);
	bernoulli_queue operator +(const bernoulli_queue &x);//���ؼӷ�
	bernoulli_queue& operator =(const bernoulli_queue &x) //���ظ�ֵ ���ø��ƺ���
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
	struct treenode				//�����ֵ����ڵ���
	{
		treenode *son,*brother;
		Type data;
		treenode():son(NULL),brother(NULL){};
		treenode(Type x, treenode *s=NULL, treenode *b=NULL):data(x),son(s),brother(b){};
		~treenode(){};
	};
	treenode **que;				//���и�����ָ�����
	int maxsize;
	int currentsize;
	void doublespace();			//���ӿռ�
	void clear(treenode *t);
	treenode* copytree(treenode *t)			//����һ����������
	{
		treenode *p=new treenode;
		p->data=t->data;
		p->son=NULL; p->brother=NULL;
		if (t->son != NULL) p->son=copytree(t->son);
		if (t->brother != NULL) p->brother=copytree(t->brother);
		return p;
	}
	treenode* connect(treenode *x, treenode *y)				//��yΪ����������xΪ��������
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

//���Ϻ�����ʵ��
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
		ans+=((i+1) << i);							//λ������ʵ��2�Ľ׳�
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
	for (i=0; i<currentsize; ++i)					//Ѱ����С��
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
	while (last!=NULL)				//�ϲ�ʣ�µĲ�֧���һ���µĶ���
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
void bernoulli_queue<Type>::push (const Type& value)	//�½�һ�����Ȼ�����ѹ�����
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
	treenode *carryin=NULL,*carryout=NULL;       //���ڼ��½�λ,����������..
	treenode *t;
	int maxLength;
	if (currentsize > tmp.currentsize) maxLength=currentsize;
	else maxLength=tmp.currentsize;
	int i;
	for (i=0; i<maxLength; i++)
	{
		//������������мӷ�
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
		carryin=carryout;//�´εļӷ��Ľ�λ������㵽��
		carryout=NULL;//����
	}
	if (carryin != NULL)//�������һ��λ���Ƿ��н�λ
		{ans.que[i]=carryin; carryin=NULL; ans.currentsize=maxLength+1;}
	else {ans.currentsize=maxLength;}
	tmp.~bernoulli_queue();
	return bernoulli_queue(ans);//���ø��ƹ��캯��������
}

//�򵥵Ĳ���
int main()
{
	int a;
	bernoulli_queue<int> que1,que2,que3;
	for (int i=1; i<=10; i++)					//10 -> 1
		que1.push(10-i+1);
	for (int i=1; i<=10; i++)					//1 -> 10
		que2.push(i);
	que3=que1+que2;								//�ϲ�
	for (int i=1; i<=20; i++)
	{
		a=que3.top();
		cout << que3.top() << ' ';				//���
		que3.pop();
	}
}
