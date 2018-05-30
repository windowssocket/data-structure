#ifndef _SORT_H_
#define _SORT_H_

#include<iostream>
using namespace std;

template<typename T>
int divide(T a[], int low, int high)
{
    int mid=(low+high)/2;
    bool p1=a[low]<a[mid],p2=a[mid]<a[high],p3=a[high]<a[low];
    if(!(p1^p3)) mid=low;
    if(!(p2^p3)) mid=high;
    //now the a[mid] is a reference of the mid number

    T k=a[mid];
    a[mid]=a[low];     //change the value of the a[low] and the mid
    do{
        while(high>low && k<a[high]) --high;
        if(high!=low) a[low++]=a[high];
        while(high>low && a[low]<k) ++low;
        if(low!=high) a[high--]=a[low];
    }while(high!=low);
    a[low]=k;
    return low;
}

template<typename T>
void quickSort(T a[], int low, int high)
{
    int mid;
    if(low>=high) return;
    mid=divide(a,low,high);
    quickSort(a,low,mid-1);
    quickSort(a,mid+1,high);
}

template<typename T>
void quickSort(T a[], int size)
{
    quickSort(a,0,size-1);
}

template <typename T>
int removeDiff (T a[], int size) //返回删除后仍留在A中的元素个数k
{
    quickSort(a,size);
    int k=0;
    for(int i=1; i<size; ++i)   //using insert to remove the repeated nums
        if(a[i]!=a[k]) a[++k]=a[i];
    return k+1;
}

#endif // _SORT_H_
