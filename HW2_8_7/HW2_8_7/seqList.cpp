#include"seqList.h"

template<class elemType>
seqList<elemType> seqList<elemType>::operator=(const seqList &R)  //assignment symbol overloading
{
	if(this==&R) return *this; //avoid copy itself
	else
	{
		delete[] data;
		data=new elemType[R.maxSize];
		
		for(int i=0; i<R.currentLength; ++i) data[i]=R.data[i];

		currentLength=R.currentLength;
		maxSize=R.maxSize;

		return *this;
	}
}

template<class elemType>
seqList<elemType> operator+(const seqList<elemType> &s1, const seqList<elemType> &s2)
{
	seqList<elemType> *sum=new seqList<elemType>(s1.maxSize+s2.maxSize);

	int i;
	for(i=0; i<s1.currentLength; ++i) sum->data[i]=s1.data[i]; //copy s1
	for( ; i<s1.currentLength+s2.currentLength; ++i) sum->data[i]=s2.data[i-s1.currentLength]; //copy s2

	sum->currentLength=s1.currentLength+s2.currentLength;

	return *sum;
}

template<class elemType>
void seqList<elemType>::input(elemType endElem)
{
	elemType tmp;
	cin>>tmp;
	for(int i=0; tmp!=endElem;++i){
		insert(i,tmp);
		cin>>tmp;
	}
}

/*********************************************/
/* the code below is copied from the C++book */
/*********************************************/

template<class elemType>
void seqList<elemType>::doubleSpace()
{
	elemType *tmp=data;
	maxSize*=2;
	data=new elemType[maxSize];

	for(int i=0; i<currentLength; ++i) data[i]=tmp[i];
	delete[] tmp;
}

template<class elemType>
seqList<elemType>::seqList(int initSize)
{
	if(initSize<=0) throw IllegalSize();
	data=new elemType[initSize];
	maxSize=initSize;
	currentLength=0;
}

template<class elemType>
void seqList<elemType>::insert(int i, const elemType &x)
{
	if(i<0 || i>currentLength) throw OutOfBound();
	if(currentLength==maxSize) doubleSpace();
	for(int j=currentLength; j>i; j--) data[j]=data[j-1];
	data[i]=x;
	++currentLength;
}

template<class elemType>
elemType seqList<elemType>::visit(int i)const
{
	if(i<0 || i>currentLength-1) throw OutOfBound();
	return data[i];
}

template<class elemType>
void seqList<elemType>::traverse()const
{
	cout<<'('<<data[0];
	for(int i=1; i<currentLength; ++i) cout<<','<<data[i];
	cout<<')';
}