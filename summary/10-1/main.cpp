#include <iostream>
using namespace std;

template <class T>								//用于交换两个数的值
void swapvalue(T &a, T &b)
{
	T tmp=a;
	a=b; b=tmp;
}

template <typename T>
void quickSort(T a[], int low, int high)		//快速排序函数
{
	int mid=(low+high)/2;
	int t,lowt,hight;
	T k;
	if (low>=high) return;
	if ((a[low]<=a[mid] && a[mid]<=a[high]) || (a[high]<=a[mid] && a[mid]<=a[low])) t=mid;		//在首中尾当中选择中间值作为基准元素
	if ((a[mid]<=a[low] && a[low]<=a[high]) || (a[high]<=a[low] && a[low]<=a[mid])) t=low;
	if ((a[low]<=a[high] && a[high]<=a[mid]) || (a[mid]<=a[high] && a[high]<=a[low])) t=high;
	swapvalue(a[low],a[t]);	//将选到的基准元素换到第一个
	lowt=low;
	hight=high;
	k=a[low];
	do						//以第一个元素为基准元素做分划
	{
		while (lowt<hight && a[hight]>=k) --hight;
		if (lowt<hight) {a[lowt]=a[hight]; ++lowt;}
		while (lowt<hight && a[lowt]<=k) ++lowt;
		if (lowt<hight) {a[hight]=a[lowt]; --hight;}
	}while (lowt!=hight);
	a[lowt]=k;
	mid=lowt;
	quickSort(a,low,mid-1);	//对左边区间递归排序
	quickSort(a,mid+1,high);//对右边区间递归排序
}

template <typename T>
void quickSort(T a[], int size)		//包裹函数
{
	quickSort(a,0,size-1);
}

template <typename T>
int removeDiff (T a[], int size)//去除数组中的重复元素
{
	int head=0;
	int tail=0;
	quickSort(a,size);			//先进行快速排序
	while (tail<size)			//排序完成后,可以进行逐个扫描,若一个值和前一个相同,表示是重复元素,不用加入新的数组
	{
		tail++;
		if (a[tail]!=a[head])
		{
			head++;
			a[head]=a[tail];
		}
	}
	return head;
}

//测试
int main()
{
	int a[100];
	int size;
	cout <<"请输入元素个数:";
	cin >> size;
	cout <<"请输入元素:";
	for (int i=0; i<size; i++)
	{
		cin >> a[i];;
	}
	size=removeDiff(a,size);
	cout <<"现在数组中有" << size <<"个元素\n";
	cout <<"这些元素是:";
	for (int i=0; i<size; i++)
	{
		cout << a[i] << ' ';
	}
}

