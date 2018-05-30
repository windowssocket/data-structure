#include <iostream> 
#include <string> 
using namespace std;

class OutOfBound{};

class IllegalSize{};

template<class elemType>
class seqlist		//链表类						
{
private: 
	struct node	       //链表中的节点
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

//重载+运算,用链表模拟两个整数的相加过程
//过程类似于纸上手算,从低到高逐位相加,注意进位问题
//特别注意最高位的进位问题的判断以及和数的长度问题
template<class elemType>
const seqlist<elemType> seqlist<elemType>::operator +(const seqlist<elemType> x)
{
	bool flag=false;  //进位标识符
	int i,j;  
	int maxlength=length;
	if (x.length>maxlength)
		maxlength=x.length;
	seqlist<elemType> tmp;
	for(i=0;i<maxlength;i++)
	{
		int num=0;   //记录每一位加法后的数值
		if(flag) num++;
		flag=false;
		if(length>i)
			num+=visit(i);
		if(x.length>i)
			num+=x.visit(i);
		if(num>=10)    //超过10后，数值减去10，并改变进位端
		{
			flag=true;
			num-=10;
		}
		tmp.insert(i,num);
	}
	if(flag)  //判断最高位是否要插上1
	{
		tmp.insert(maxlength,1);
		maxlength++;
	}
	tmp.length=maxlength;
	return tmp;
}

//重载赋值运算符
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
	cin.unsetf(ios_base::skipws);  //为了能够在CMD窗口中输入时不忽略空格和回车符
	cout<<"This is the driving program for 2-11 adding two integers"<<endl;
	cout<<"请输入第一个数字: ";
    cin>>ch1;
	while(ch1!='\n')
	{
		a.insert(0,ch1-'0');  //利用character中0-9数字排列连续,并且每个新元素都插到以前元素的前面
		cin>>ch1;
	}
	cout<<"请输入第二个数字: ";
	cin>>ch2;
   	while(ch2!='\n')
	{
	     b.insert(0,ch2-'0');
		 cin>>ch2;
	}
	c=a+b;
	int l=c.getlength();
	cout<<"两数之和为: ";
	for (int i=l-1;i>=0;i--)  //由于数字是逆序存储的,因此,逆序输出才是数字本身
	{
		cout<<c.visit(i);
	}
	cout<<endl;
	system("pause");
}