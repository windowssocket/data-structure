#include <iostream>
using namespace std;

template <typename Type>
class List		//���Ա���(������ʵ��)
{
private:
	struct node		//���ṹ
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

//���ֺ�����ʵ��
template <typename Type>
List<Type>::List()
{
	length=0;
	head=new node;
}

//����һ��Ԫ�ص����
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

//���������Ԫ�أ����Ұ����ᵽ��һλ����ͷ��
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
		}  //���ұ����Ƿ���ָ����Ԫ��
		p=p->next;
	}
	if (ans)
	{
		tmp=p->next;
		p->next=tmp->next;
		tmp->next=head->next;
		head->next=tmp;
	}   //����ҵ���ָ����Ԫ�أ������Ԫ�طŵ���ͷ
	return ans;
}

template <typename Type>
void List<Type>::returnhead()
{
    cout << head->next->data <<endl;
}  //�����ͷԪ��

//����
int main()
{
	List<int> list;
	for (int i=1; i<=10; i++)
	{
		list.Insert(i);
	}
	if (list.Find(2)) cout << "�ҵ���2\n";
	cout << "���ڱ�ͷԪ��Ϊ" ;
	list.returnhead();
	if (!list.Find(11)) cout << "û���ҵ�11\n";
}
