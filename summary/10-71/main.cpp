#include <iostream>
using namespace std;

template <class Type>
void percolateDown(int hole, Type a[],int& size)			//�ѵ����µ�������
{
	int child;
	Type tmp=a[hole];
	for (; hole*2<=size; hole=child)
	{
		child=hole*2;
		if (child!=size && a[child+1]>a[child]) child++;	//ά������
		if (a[child]>tmp) a[hole]=a[child];
		else break;
	}
	a[hole]=tmp;
}

template <class Type>
void buildHeap(Type a[], int& size)		//��size/2 -> 1 ��˳�����µ���������
{
	for (int i=size/2; i>0; i--)
		percolateDown(i,a,size);
}

template <class Type>
Type dequeue(Type a[],int& size)		//�Ӷ��е������Ԫ��(������)
{
	Type max=a[1];
	a[1]=a[size--];
	percolateDown(1,a,size);
	return max;
}

int main()
{
	int a[1000];
	int size,i,k;
	cout << "������k��ֵ: "; cin >> k;
	cout << "�����������С: "; cin >> size;
	cout << "������ÿ��Ԫ��:";
	for (i=1; i<=size; i++)
	{
		cin >> a[i];
	}												//��������
	buildHeap(a,size);								//����
	for (i=1; i<k; i++)								//�Ӷ��е���k-1��Ԫ��
		dequeue(a,size);
	cout << "��" << k <<"���Ԫ����: ";
	cout << dequeue(a,size);						//�����ĵ�k��Ԫ�ؾ��ǵ�k���Ԫ��
}

