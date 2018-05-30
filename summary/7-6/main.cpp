#include <iostream>
using namespace std;

template <typename Type>
class List		//线性表类(单链表实现)
{
private:
	struct node		//结点结构
	{
		Type data;
		node *next;
		node():next(NULL){}
		node(const Type &x, node *n=NULL)
		{
			data=x;
			next=n;
		}
	};
	node *head;
	int length;

public:
	  List();
	  ~List(){}
	  int getlength() const {return length;}
	  void Insert(Type x);
	  bool Find(Type x);
	  void returnhead();
};

//各种函数的实现
template <typename Type>
List<Type>::List()
{
	length=0;
	head=new node;
}

//插入一个元素到最后
template <typename Type>
void List<Type>::Insert(Type x)
{
	node *p=head;
	while (p->next!=NULL)
	{
		p=p->next;
	}
	node *tmp;
	tmp=new node(x,p->next);
	p->next=tmp;
	length++;
}

//查找所需的元素，并且把它提到第一位（表头）
template <typename Type>
bool List<Type>::Find(Type x)
{
	bool ans=false;
	node *p=head;
	node *tmp;
	for (int i=0; i<length; i++)
	{
		if (p->next->data==x)
		{
			ans=true;
			break;
		}  //查找表中是否有指定的元素
		p=p->next;
	}
	if (ans)
	{
		tmp=p->next;
		p->next=tmp->next;
		tmp->next=head->next;
		head->next=tmp;
	}   //如果找到了指定的元素，把这个元素放到表头
	return ans;
}

template <typename Type>
void List<Type>::returnhead()
{
    cout << head->next->data <<endl;
}  //输出表头元素

//测试
int main()
{
	List<int> list;
	for (int i=1; i<=10; i++)
	{
		list.Insert(i);
	}
	if (list.Find(2)) cout << "找到了2\n";
	cout << "现在表头元素为" ;
	list.returnhead();
	if (!list.Find(11)) cout << "没有找到11\n";
}
