#include <iostream>
using namespace std;

template<class elemType>
class list                        //线性表抽象类
{ 
    public:
      virtual void clear()=0;
	  virtual int  length() const=0;
	  virtual void insert (int i,const elemType &x)=0;
	  virtual void remove (int i)=0;
	  virtual int search (const elemType &x)const=0;
	  virtual elemType visit (int i)const=0;
	  virtual void traverse() const=0;
	  virtual ~list(){};
};

class OutOfBound{};

class IllegalSize{};

template<class elemType>
class seqlist:public list <elemType>              //线性表类与实现
{
private:
      elemType *data;
	  int currentLength;
	  int maxSize;
	  
	  void doublespace();
public:
	  seqlist(int initSize=10);
	  ~seqlist(){}
	  void clear(){currentLength=0;}
	  int length() const {return currentLength;}
	  void insert(int i,const elemType &x);
	  void remove(int i);
	  int search(const elemType &x) const;
	  elemType visit(int i) const;
	  void traverse() const;
	  const seqlist<elemType> operator + (const seqlist<elemType> x);
      seqlist<elemType> &operator = (const seqlist<elemType> &x);
};

template<class elemType>
void seqlist<elemType>::doublespace()
{
	elemType*tmp=data;
	maxSize*=2;
	data=new elemType[maxSize];
	for (int i=0;i<currentLength;i++) data[i]=tmp[i];
	delete []tmp;
 }

template<class elemType>
seqlist<elemType>::seqlist(int initSize)
{
	if(initSize<=0) throw IllegalSize();
	data=new elemType[initSize];
	maxSize=initSize;
	currentLength=0;
}

template<class elemType>
void seqlist<elemType>::insert(int i,const elemType &x)
{
	if(i<0||i>currentLength) throw OutOfBound();
	if(currentLength==maxSize) doublespace();
	for(int j=currentLength;j>i;j--) 
		data[j]=data[j-1];
	data[i]=x;
	currentLength++;
}

template<class elemType>
void seqlist<elemType>::remove(int i)
{
	if (i<0||i>currentLength-1) throw OutOfBound();
	for(int j=i;j<currentLength-1;j++) 
		data[j]=data[j+1];
	currentLength--;
}

template<class elemType>
int seqlist<elemType>::search(const elemType &x)const
{
	int i;
	for(i=0;i<currentLength&&data[i]!= x;++i);
	if(i==currentLength) return -1; else return i;
}

template<class elemType>
elemType seqlist<elemType>::visit(int i) const
{
	if(i<0||i>currentLength-1) throw OutOfBound();
	return data[i];
}

template<class elemType>
void seqlist<elemType>::traverse()const
{
	for(int i=0;i<currentLength;++i) cout<<data[i]<<' ';
}

//重载加号运算
template<class elemType>
const seqlist<elemType> seqlist<elemType>::operator +(const seqlist<elemType> x)
{
	int length=currentLength+x.currentLength;
	int max=maxSize+x.maxSize;//相加后的线性表长度是两个相加的线性表长度相加
	int i,j;  
	seqlist<elemType> tmp(max);
	tmp.currentLength=length;
	for(i=0;i<currentLength;i++)
		tmp.data[i]=data[i];
	for(j=currentLength;j<length;j++) 
		tmp.data[j]=x.data[j-currentLength];//合并两个线性表，并存入tmp中
	return tmp;//返回tmp
}

//重载赋值运算
template<class elemType>
seqlist<elemType>& seqlist<elemType>::operator =(const seqlist<elemType> &x)
{
    maxSize=x.maxSize;
	currentLength=x.currentLength;
	delete []data;
	data=new elemType[maxSize];
	for(int i=0;i<currentLength;i++)
		data[i]=x.data[i];
	return *this;
}

//用整数情况来测试的测试程序
int main()
{
	cout<<"This is the driving program for 2-7 using integers"<<endl;
	int m,n;
	int temp;
	cout<<"请输入A表中的元素个数: ";
	cin>>m;
	cout<<"请输入B表中的元素个数: ";
	cin>>n;
	seqlist<int> a(m),b(n),c(m+n);
	cout <<"请逐个输入A表中的元素(每个元素以空格隔开)"<<endl;
	for (int i=0;i<m;i++)
	{
		cin>>temp;
		a.insert(i,temp);
	}
	cout<<"请逐个输入B表中的元素(每个元素以空格隔开)"<<endl;
	for(int i=0;i<n;i++)
	{
		cin>>temp;
		b.insert(i,temp);
	}
	c=a+b;
	cout<<"合并后的线性表中内容为： ";
	c.traverse();
	cout<<endl;
	system("pause");
}