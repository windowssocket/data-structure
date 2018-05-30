#include <iostream>
using namespace std;

template <class T>								//���ڽ�����������ֵ
void swapvalue(T &a, T &b)
{
	T tmp=a;
	a=b; b=tmp;
}

template <typename T>
void quickSort(T a[], int low, int high)		//����������
{
	int mid=(low+high)/2;
	int t,lowt,hight;
	T k;
	if (low>=high) return;
	if ((a[low]<=a[mid] && a[mid]<=a[high]) || (a[high]<=a[mid] && a[mid]<=a[low])) t=mid;		//������β����ѡ���м�ֵ��Ϊ��׼Ԫ��
	if ((a[mid]<=a[low] && a[low]<=a[high]) || (a[high]<=a[low] && a[low]<=a[mid])) t=low;
	if ((a[low]<=a[high] && a[high]<=a[mid]) || (a[mid]<=a[high] && a[high]<=a[low])) t=high;
	swapvalue(a[low],a[t]);	//��ѡ���Ļ�׼Ԫ�ػ�����һ��
	lowt=low;
	hight=high;
	k=a[low];
	do						//�Ե�һ��Ԫ��Ϊ��׼Ԫ�����ֻ�
	{
		while (lowt<hight && a[hight]>=k) --hight;
		if (lowt<hight) {a[lowt]=a[hight]; ++lowt;}
		while (lowt<hight && a[lowt]<=k) ++lowt;
		if (lowt<hight) {a[hight]=a[lowt]; --hight;}
	}while (lowt!=hight);
	a[lowt]=k;
	mid=lowt;
	quickSort(a,low,mid-1);	//���������ݹ�����
	quickSort(a,mid+1,high);//���ұ�����ݹ�����
}

template <typename T>
void quickSort(T a[], int size)		//��������
{
	quickSort(a,0,size-1);
}

//����
int main()
{
	int a[100];
	int size;
	cout <<"������Ԫ�ظ���:";
	cin >> size;
	cout <<"������Ԫ��:";
	for (int i=0; i<size; i++)
	{
		cin >> a[i];;
	}
	quickSort(a, size);
	cout <<"��С�������к��Ԫ����:";
	for (int i=0; i<size; i++)
	{
		cout << a[i] << ' ';
	}
}



