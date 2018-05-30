#include <iostream>
using namespace std;

template <class Type>
void percolateDown(int hole, Type a[],int& size)			//堆的向下调整策略
{
	int child;
	Type tmp=a[hole];
	for (; hole*2<=size; hole=child)
	{
		child=hole*2;
		if (child!=size && a[child+1]>a[child]) child++;	//维护最大堆
		if (a[child]>tmp) a[hole]=a[child];
		else break;
	}
	a[hole]=tmp;
}

template <class Type>
void buildHeap(Type a[], int& size)		//用size/2 -> 1 的顺序向下调整建最大堆
{
	for (int i=size/2; i>0; i--)
		percolateDown(i,a,size);
}

template <class Type>
Type dequeue(Type a[],int& size)		//从堆中弹出最大元素(队列首)
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
	cout << "请输入k的值: "; cin >> k;
	cout << "请输入数组大小: "; cin >> size;
	cout << "请输入每个元素:";
	for (i=1; i<=size; i++)
	{
		cin >> a[i];
	}												//读入数据
	buildHeap(a,size);								//建堆
	for (i=1; i<k; i++)								//从堆中弹出k-1个元素
		dequeue(a,size);
	cout << "第" << k <<"大的元素是: ";
	cout << dequeue(a,size);						//弹出的第k个元素就是第k大的元素
}

