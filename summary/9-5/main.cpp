#include <iostream>
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

int main()
{
	closeHashTable<int> hashlist(7);
	hashlist.insert(1);
	hashlist.remove(1);
	hashlist.insert(1);
	hashlist.remove(1);
	hashlist.insert(8);
	hashlist.insert(1);
	if (hashlist.find(1))
		cout << "找到了1" << endl;
	else cout << "没有找到1" << endl;
	return 0;
}
