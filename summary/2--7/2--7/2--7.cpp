#include <iostream>
using namespace std;

template<class elemType>
class list                        //���Ա������
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
class seqlist:public list <elemType>              //���Ա�����ʵ��
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

//���ؼӺ�����
template<class elemType>
const seqlist<elemType> seqlist<elemType>::operator +(const seqlist<elemType> x)
{
	int length=currentLength+x.currentLength;
	int max=maxSize+x.maxSize;//��Ӻ�����Ա�����������ӵ����Ա������
	int i,j;  
	seqlist<elemType> tmp(max);
	tmp.currentLength=length;
	for(i=0;i<currentLength;i++)
		tmp.data[i]=data[i];
	for(j=currentLength;j<length;j++) 
		tmp.data[j]=x.data[j-currentLength];//�ϲ��������Ա�������tmp��
	return tmp;//����tmp
}

//���ظ�ֵ����
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

//��������������ԵĲ��Գ���
int main()
{
	cout<<"This is the driving program for 2-7 using integers"<<endl;
	int m,n;
	int temp;
	cout<<"������A���е�Ԫ�ظ���: ";
	cin>>m;
	cout<<"������B���е�Ԫ�ظ���: ";
	cin>>n;
	seqlist<int> a(m),b(n),c(m+n);
	cout <<"���������A���е�Ԫ��(ÿ��Ԫ���Կո����)"<<endl;
	for (int i=0;i<m;i++)
	{
		cin>>temp;
		a.insert(i,temp);
	}
	cout<<"���������B���е�Ԫ��(ÿ��Ԫ���Կո����)"<<endl;
	for(int i=0;i<n;i++)
	{
		cin>>temp;
		b.insert(i,temp);
	}
	c=a+b;
	cout<<"�ϲ�������Ա�������Ϊ�� ";
	c.traverse();
	cout<<endl;
	system("pause");
}