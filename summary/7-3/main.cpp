#include <iostream>
using namespace std;

template <typename Type>
class Set
{
public:
	Set();
	Set(const Set &x);
	~Set();
	void add(Type x);						//�򼯺ϼ���Ԫ��
	void show();							//�鿴Ԫ��
	Set<Type> operator *(const Set &x);		//*����
	Set<Type> operator +(const Set &x);		//+����
	Set<Type> operator -(const Set &x);		//-����
	Set<Type>& operator =(const Set &x);	//=����
private:
	int maxSize;							//���Size
	int length;								//��ǰ����
	Type *data;
	void doublespace();
};

template <typename Type>
Set<Type>::Set(const Set &x)				//���ƹ��캯��
{
	maxSize=x.maxSize;
	length=x.length;
	data=new Type[maxSize];
	for (int i=0; i<=length; i++) data[i]=x.data[i];
}

template <typename Type>
Set<Type>::Set()							//��ͨ���캯��
{
	length=0;
	maxSize=100;
	data=new Type[maxSize+1];
}

template <typename Type>
Set<Type>::~Set()							//��������
{
	delete []data;
}

template <typename Type>
void Set<Type>::doublespace()				//��������
{
	Type *tmp=data;
	maxSize*=2;
	data=new Type[maxSize];
	for (int i=1; i<=length; ++i)
		data[i]=tmp[i];
	delete [] tmp;
}

//����ʵ��
template <typename Type>
Set<Type> Set<Type>::operator*(const Set &x)  //������
{
	int i;
	Set tmp;
	for (i=1; i<=x.length; i++)
		tmp.add(x.data[i]);
	for (i=1; i<=length; i++)
		tmp.add(data[i]);  //add�����ĺô������ظ�Ԫ�ز�����뼯��
	return Set(tmp);
}

template <typename Type>  //������
Set<Type> Set<Type>::operator+(const Set &x)
{
	int i,j;
	bool flag;  //������������Ƿ�����ͬԪ��
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
		}   //�������ϵ�Ԫ�طֱ�Ƚ��Ƿ�����ͬ��Ԫ��
		if (flag)
		{
			tmp.add(x.data[i]);
		}   //������ͬ��Ԫ�أ������Ԫ�ط��뽻����
	}
	return Set(tmp);
}

template <typename Type>
Set<Type> Set<Type>::operator-(const Set &x)  //����������ܺ�������ķ�����
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
	}  //�ѱ��������е������������ͬ��Ԫ��ȥ������������
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

//�ж�Ԫ��ʱ�������Ԫ���Ƿ��ظ�,�����ظ��ͼ��뼯����
template <typename Type>
void Set<Type>::add(Type x)
{
	for (int i=1; i<=length; i++)
		if (data[i]==x) return;  //���ظ�����������
	length++;
	if (length>=maxSize-1) doublespace();
	data[length]=x;  //�����Ԫ�ؼ��뼯��
}

//��������е�Ԫ��
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
	cout <<"a*b(������)��ļ���Ϊ��";
	c.show();
	cout <<"a+b(������)��ļ���Ϊ��";
	c=a+b;
	c.show();
	cout <<"a-b(������)��ļ���Ϊ��";
	c=a-b;
	c.show();
}
