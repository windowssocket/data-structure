#include <iostream>
using namespace std;

template <class Type>
void percolateDown(int hole, Type a[], int& size)			//向下调整
{
	int child;
	Type tmp=a[hole];
	for (; hole*2<=size; hole=child)
	{
		child=hole*2;
		if (child!=size && a[child+1]<a[child]) child++;	//构建最小堆
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
Type dequeue(Type a[],int& size)			//弹出堆首元素
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
	cout << "请输入k的值: "; cin >> k;
	cout << "请输入数组大小: "; cin >> size;
	cout << "请输入数组中的元素: ";
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
		}       //如果i小于等于k，调用percolateUp函数，使前k个元素成为最小堆
		if (a[i]>a[1])
		{
			a[1]=a[i];
			percolateDown(1,a,k);
		}       //否则的话，用第i个元素与第1个元素比较，如果比第1个元素大，则代替第1个元素，并形成最小堆
	}
	cout <<"第" <<k <<"大的元素是" <<a[1];    //经过size次，最小堆中第1个元素便是第k大的元素
}

