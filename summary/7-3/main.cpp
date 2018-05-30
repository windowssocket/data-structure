#include <iostream>
using namespace std;

template <typename Type>
class Set
{
public:
	Set();
	Set(const Set &x);
	~Set();
	void add(Type x);						//向集合加入元素
	void show();							//查看元素
	Set<Type> operator *(const Set &x);		//*重载
	Set<Type> operator +(const Set &x);		//+重载
	Set<Type> operator -(const Set &x);		//-重载
	Set<Type>& operator =(const Set &x);	//=重载
private:
	int maxSize;							//最大Size
	int length;								//当前长度
	Type *data;
	void doublespace();
};

template <typename Type>
Set<Type>::Set(const Set &x)				//复制构造函数
{
	maxSize=x.maxSize;
	length=x.length;
	data=new Type[maxSize];
	for (int i=0; i<=length; i++) data[i]=x.data[i];
}

template <typename Type>
Set<Type>::Set()							//普通构造函数
{
	length=0;
	maxSize=100;
	data=new Type[maxSize+1];
}

template <typename Type>
Set<Type>::~Set()							//析构函数
{
	delete []data;
}

template <typename Type>
void Set<Type>::doublespace()				//容量翻倍
{
	Type *tmp=data;
	maxSize*=2;
	data=new Type[maxSize];
	for (int i=1; i<=length; ++i)
		data[i]=tmp[i];
	delete [] tmp;
}

//重载实现
template <typename Type>
Set<Type> Set<Type>::operator*(const Set &x)  //并运算
{
	int i;
	Set tmp;
	for (i=1; i<=x.length; i++)
		tmp.add(x.data[i]);
	for (i=1; i<=length; i++)
		tmp.add(data[i]);  //add函数的好处就是重复元素不会放入集合
	return Set(tmp);
}

template <typename Type>  //交运算
Set<Type> Set<Type>::operator+(const Set &x)
{
	int i,j;
	bool flag;  //标记两个集合是否有相同元素
	Set tmp;
	for (i=1; i<=x.length; i++)
	{
		flag=false;
		for (j=1; j<=length; j++)
		{
			if (x.data[i]==data[j])
			{
				flag=true;
				break;
			}
		}   //两个集合的元素分别比较是否有相同的元素
		if (flag)
		{
			tmp.add(x.data[i]);
		}   //若有相同的元素，把这个元素放入交集合
	}
	return Set(tmp);
}

template <typename Type>
Set<Type> Set<Type>::operator-(const Set &x)  //这个函数功能好像交运算的反运算
{
	int i,j;
	bool flag;
	Set tmp;
	for (i=1; i<=length; i++)
	{
		flag=true;
		for (j=1; j<=x.length; j++)
		{
			if (x.data[j]==data[i])
			{
				flag=false;
				break;
			}
		}
		if (flag)
		{
			tmp.add(data[i]);
		}
	}  //把被减集合中的与减集合中相同的元素去掉，不放入差集合
	return Set(tmp);
}

template <typename Type>
Set<Type>& Set<Type>::operator=(const Set &x)
{
	length=x.length;
	while (x.length>=maxSize-1) doublespace();
	for (int i=1; i<=x.length; i++)
		data[i]=x.data[i];
	return *this;
}

//判断元素时候和已有元素是否重复,若不重复就加入集合中
template <typename Type>
void Set<Type>::add(Type x)
{
	for (int i=1; i<=length; i++)
		if (data[i]==x) return;  //若重复，跳出函数
	length++;
	if (length>=maxSize-1) doublespace();
	data[length]=x;  //否则把元素加入集合
}

//输出集合中的元素
template <typename Type>
void Set<Type>::show()
{
	for (int i=1; i<=length; i++)
		cout << data[i] << ' ';
	cout << endl;
}

int main()
{
	Set<int> a,b,c;
	for (int i=1; i<=10; i++)
	{
		a.add(i);
		b.add(i+2);
	}
	c=a*b;
	cout <<"a*b(并运算)后的集合为：";
	c.show();
	cout <<"a+b(交运算)后的集合为：";
	c=a+b;
	c.show();
	cout <<"a-b(差运算)后的集合为：";
	c=a-b;
	c.show();
}
