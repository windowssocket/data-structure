#include"GH_SeqList.h"

template <class ElemType> 
SeqList<ElemType>::SeqList(int InitSize)
{
	if(InitSize<1) MaxSize=1;  //InitSize should be larger than 1
	else MaxSize=InitSize;

	length=0;
	elem=new ElemType[MaxSize+1];
}


template <class ElemType> 
SeqList<ElemType>::~SeqList()
{
	delete[] elem;
}


template <class ElemType> 
void SeqList<ElemType>::Clear()
{
	length=0;
}


template <class ElemType> 
bool SeqList<ElemType>::IsEmpty()
{
	return !(length);
}


template <class ElemType> 
int SeqList<ElemType>::Length()
{
	return length;
}


template <class ElemType> 
ElemType SeqList<ElemType>::Get(int i) const
{
	if(i>length) return 0;
	else return elem[i];
}


template <class ElemType> 
int SeqList<ElemType>::Find(ElemType e) const
{
	int i;    //the order of the e elem
	elem[0]=e;

	for(i=length; i>=0; --i)
		if(elem[i]==e) break;

	return i;
}


template <class ElemType> 
int SeqList<ElemType>::Insert(int i, ElemType e)
{
	if(length==MaxSize) return 0;
	else
	{
		for(int j=length; j>=i; --j) elem[j+1]=elem[j];

		elem[i]=e;
		++length;

		return 1;
	}
}


template <class ElemType> 
ElemType SeqList<ElemType>::Delete(int i)
{
	if(i<1 || i>length) return 0;
	else
	{
		ElemType del=elem[i];
		for(int j=i; j<length; ++j) elem[j]=elem[j+1];

		--length;
		return del;
	}
}

