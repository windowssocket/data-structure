#include <iostream>
using namespace std;

template <class Type>
void percolateDown(int hole, Type a[], int& size)			//���µ���
{
	int child;
	Type tmp=a[hole];
	for (; hole*2<=size; hole=child)
	{
		child=hole*2;
		if (child!=size && a[child+1]<a[child]) child++;	//������С��
		if (a[child]<tmp) a[hole]=a[child];
		else break;
	}
	a[hole]=tmp;
}

template <class Type>
void percolateUp(Type x, Type a[], int& size)
{
	size++;
	int hole=size;
	for (;hole>1 && x<a[hole/2]; hole/=2)
		a[hole]=a[hole/2];
	a[hole]=x;
}

template <class Type>
Type dequeue(Type a[],int& size)			//��������Ԫ��
{
	Type max=a[1];
	a[1]=a[size--];
	percolateDown(1,a,size);
	return max;
}

int main()
{
	int a[100];
	int size,i,k;
	cout << "������k��ֵ: "; cin >> k;
	cout << "�����������С: "; cin >> size;
	cout << "�����������е�Ԫ��: ";
	for (i=1; i<=size; i++)
	{
		cin >> a[i];
	}
	for (i=1; i<=size; i++)
	{
		if (i<k+1)
		{
			percolateUp(a[i],a,i);
			continue;
		}       //���iС�ڵ���k������percolateUp������ʹǰk��Ԫ�س�Ϊ��С��
		if (a[i]>a[1])
		{
			a[1]=a[i];
			percolateDown(1,a,k);
		}       //����Ļ����õ�i��Ԫ�����1��Ԫ�رȽϣ�����ȵ�1��Ԫ�ش�������1��Ԫ�أ����γ���С��
	}
	cout <<"��" <<k <<"���Ԫ����" <<a[1];    //����size�Σ���С���е�1��Ԫ�ر��ǵ�k���Ԫ��
}

