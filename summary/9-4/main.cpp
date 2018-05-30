#include <iostream>
#include <time.h>
#include <stdlib.h>
using namespace std;

static int defaultKey(const int &k) {return k;}

//哈希表基类
template <class Type>
class hashTable
{
public:
	virtual bool find(const Type &x) const=0;
	virtual bool insert(const Type &x) =0;
	virtual bool remove(const Type &x) =0;
};

//闭散列表派生类
template <class Type>
class closeHashTable:public hashTable<Type>
{
private:
	struct node//结点
	{
		Type data;
		int state;
		node() {state=0;}
	};
	node *array;//数组单元
	int size,num,deleted,limit;//长度 有效元素个数 被删除元素个数 用户指定的被删除元素的最大个数
	void doublespace()//扩增空间
	{
		size=size*2;
		node *tmp=array;
		array=new node[size];
		num=0; deleted=0;
		for (int i=0; i<(size/2); i++)
		{
			if (tmp[i].state==1) insert(tmp[i].data);
		}
		delete [] tmp;
	}
public:
	closeHashTable(int length=101, int lim=1, int (*f)(const Type &x)=defaultKey);//构造函数
	~closeHashTable(){delete [] array;}//析构函数
	bool find(const Type &x) const;//查找
	bool insert(const Type &x);//插入
	bool remove(const Type &x);//删除
	void rehash();//重新散列
protected:
	int (* key)(const Type &x);
};

//各个函数的实现
template <class Type>
closeHashTable<Type>::closeHashTable(int length, int lim , int (* f)(const Type &x))
{
	size=length;
	limit=lim;
	num=0;
	deleted=0;
	array=new node[size];
	key=f;
}

//插入函数实现
template <class Type>
bool closeHashTable<Type>::insert(const Type &x)
{
	int initPos,pos;
	initPos=pos=key(x) % size;
	do
	{
		if (array[pos].state!=1)
		{
			array[pos].data=x;
			array[pos].state=1;
			num++;										//记录有效元素个数,并判断是否达到容量的一半,若达到则扩增容量
			if (num>=(size/2)) doublespace();
			return true;
		}
		if (array[pos].state==1 && array[pos].data==x)
			return true;
		pos=(pos+1) % size;
	}while (pos!=initPos);
	return false;
}

//删除函数的实现
template <class Type>
bool closeHashTable<Type>::remove(const Type &x)
{
	int initPos,pos;
	initPos=pos=key(x) % size;
	do
	{
		if (array[pos].state==0) return false;
		if (array[pos].state==1 && array[pos].data==x)
		{
			array[pos].state=2;
			num--;										//若删除成功,则有效元素减少一个
			deleted++;									//被删除元素增加一个
			if (deleted>=limit) rehash();			//若被删元素多与容量的一般,则重新散列
			return true;
		}
		pos=(pos+1) % size;
	}while (pos!=initPos);
	return false;
}

//查找函数的实现
template <class Type>
bool closeHashTable<Type>::find(const Type &x) const
{
	int initPos,pos;
	initPos=pos=key(x) % size;
	do
	{
		if (array[pos].state==0) return false;
		if (array[pos].state==1 && array[pos].data==x) return true;
		pos=(pos+1) % size;
	}while (pos!=initPos);
	return false;
}

//重新散列函数
template <class Type>
void closeHashTable<Type>::rehash()
{
	node *tmp=array;
	array=new node[size];
	for (int i=0; i<size; i++)
	{
		if (tmp[i].state==1) insert(tmp[i].data);
	}
	deleted=0;					//重新散列后,被删元素(标记为2的元素)数量为0
	delete [] tmp;
}

class matrix{
    public:
        matrix(int r,int c,int d):row(r),column(c),data(d){}
        matrix(){}
        bool operator==(const matrix &d)
        {
            if(row==d.row&&column==d.column) return true;
            else return false;
        }
        int row,column,data;
};

static int getkey(const matrix& a)
{
    return a.row*100+a.column;
}

int main()
{
    closeHashTable< matrix >hashlist(131,5,getkey);
    int r,d,count,i,j;
    double k;
    count=0;
    srand(time(NULL));
    for(i=0;i<100;i++)
    {
        for(j=0;j<100;j++)
        {
            r=rand()*100/(RAND_MAX+1);     //生成非零的概率
            if(r!=0) continue;             //对应的元素值为零
            d=rand()*1000/(RAND_MAX+1)+1;   //生成矩阵元素值
            matrix b(i,j,d);
            hashlist.insert(b);
            ++count;
        }
    }
    k=(double)count/10000.0*100.0;
    cout<<"10000个元素中有"<<count<<"个非零元素"<<"占"<<k<<"%"<<endl;
}

