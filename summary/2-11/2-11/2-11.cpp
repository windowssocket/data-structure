#include <iostream> 
#include <string> 
using namespace std;

class OutOfBound{};

class IllegalSize{};

template<class elemType>
class seqlist		//������						
{
private: 
	struct node	       //�����еĽڵ�
	{
		elemType data;
		node *next;
		node():next(NULL){}
		node(const elemType &x,node *n=NULL)
		{
			data=x;
			next=n;
		}
	};
	node *head;
	int length;

public:
	  seqlist();
	  ~seqlist(){}
	  int getlength() const {return length;}
	  void insert(int i,const elemType &x);
	  void remove(int i);
	  int search(const elemType &x) const;
	  elemType visit(int i) const;
	  void traverse() const;
	  const seqlist<elemType> operator +(const seqlist<elemType> x);
      seqlist<elemType> &operator =(const seqlist<elemType> &x);
};

template<class elemType>
seqlist<elemType>::seqlist()
{
	length=0;
	head=new node;
}

template<class elemType>
void seqlist<elemType>::insert(int i,const elemType &x)
{
	node *p=head;
	for (int j=0;j<i;j++)
		p=p->next;
	node *tmp;
	tmp=new node(x,p->next);
	p->next=tmp;
	length++;
}

template<class elemType>
elemType seqlist<elemType>::visit(int i) const
{
	if(i<0||i>length-1) throw OutOfBound();
	node *p=head->next;
	for (int j=0;j<i;j++)
		p=p->next;
	return (p->data);
}

//����+����,������ģ��������������ӹ���
//����������ֽ������,�ӵ͵�����λ���,ע���λ����
//�ر�ע�����λ�Ľ�λ������ж��Լ������ĳ�������
template<class elemType>
const seqlist<elemType> seqlist<elemType>::operator +(const seqlist<elemType> x)
{
	bool flag=false;  //��λ��ʶ��
	int i,j;  
	int maxlength=length;
	if (x.length>maxlength)
		maxlength=x.length;
	seqlist<elemType> tmp;
	for(i=0;i<maxlength;i++)
	{
		int num=0;   //��¼ÿһλ�ӷ������ֵ
		if(flag) num++;
		flag=false;
		if(length>i)
			num+=visit(i);
		if(x.length>i)
			num+=x.visit(i);
		if(num>=10)    //����10����ֵ��ȥ10�����ı��λ��
		{
			flag=true;
			num-=10;
		}
		tmp.insert(i,num);
	}
	if(flag)  //�ж����λ�Ƿ�Ҫ����1
	{
		tmp.insert(maxlength,1);
		maxlength++;
	}
	tmp.length=maxlength;
	return tmp;
}

//���ظ�ֵ�����
template<class elemType>
seqlist<elemType>& seqlist<elemType>::operator =(const seqlist<elemType> &x)
{
	for(int i=0;i<x.length;i++)
		insert(i,x.visit(i));
	return *this;
}

int main()
{
	seqlist<int> a,b,c; 
	char ch1;
	char ch2;
	cin.unsetf(ios_base::skipws);  //Ϊ���ܹ���CMD����������ʱ�����Կո�ͻس���
	cout<<"This is the driving program for 2-11 adding two integers"<<endl;
	cout<<"�������һ������: ";
    cin>>ch1;
	while(ch1!='\n')
	{
		a.insert(0,ch1-'0');  //����character��0-9������������,����ÿ����Ԫ�ض��嵽��ǰԪ�ص�ǰ��
		cin>>ch1;
	}
	cout<<"������ڶ�������: ";
	cin>>ch2;
   	while(ch2!='\n')
	{
	     b.insert(0,ch2-'0');
		 cin>>ch2;
	}
	c=a+b;
	int l=c.getlength();
	cout<<"����֮��Ϊ: ";
	for (int i=l-1;i>=0;i--)  //��������������洢��,���,��������������ֱ���
	{
		cout<<c.visit(i);
	}
	cout<<endl;
	system("pause");
}