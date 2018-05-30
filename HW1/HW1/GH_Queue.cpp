#include"GH_Queue.h"

template<class ElemType>
Queue<ElemType>::Queue()  	//maxSize is 10
{
	begin=0;
	size=0;
	maxSize=10;
	data=new ElemType[maxSize];
}


template<class ElemType>
Queue<ElemType>::Queue(int length)
{
	begin=0;
	size=0;

	if(length<1)
	{
		cerr<<"队列最大长度不能设为"<<length<<endl;  //report error
		throw(length);
	}

	maxSize=length;
	data=new ElemType[maxSize];
}


template<class ElemType>
Queue<ElemType>::Queue(Queue &R)
{
	int i;

	if(this==&R) return;  //avoid copy itself
	else
	{
		data=new ElemType[R.maxSize];
		
		for(i=0; i<R.maxSize; ++i) data[i]=R.data[i];

		begin=R.begin;
		size=R.size;
		maxSize=R.maxSize;
	}
}


template<class ElemType>
Queue<ElemType>::~Queue()
{
	delete[] data;
}


template<class ElemType>
bool Queue<ElemType>::IsFull()const
{
	if(size==maxSize) return true;
	else return false;
}


template<class ElemType>
bool Queue<ElemType>::IsEmpty()const
{
	if(size==0) return true;
	else return false;
}


template<class ElemType>
bool Queue<ElemType>::Enqueue(const ElemType &elem)
{
	if(size==maxSize) return false;  //if queue is full return false
		
	data[(begin+size)%maxSize]=elem;
	++size;
	
	return true;

}


template<class ElemType>
ElemType Queue<ElemType>::Dequeue()
{
	ElemType delElem;  //temporary storage of the deleted data

	if(size==0) return false;   //if the queue is empty return false

	delElem=data[begin];
	begin=(++begin)%maxSize;
	--size;

	return delElem;

}


template<class ElemType>
ElemType Queue<ElemType>::Peek(int i)const
{
	if(i>=size) return 0;   //if the position is unreasonable ,return 0
	else return data[(begin+i)%maxSize];
}


template<class ElemType>
int Queue<ElemType>::GetSize()const
{
	return size;
}


template<class ElemType>
void Queue<ElemType>::Display()const
{
	int i;

	if(size==0) cout<<"the queue is empty"<<endl;
	else
	{
		cout<<"There are "<<size<<" elements in the queue. They are:"<<endl;
		for(i=0; i<size; ++i) cout<<data[(begin+i)%maxSize]<<"  ";
		cout<<endl;
	}

}


template<class ElemType>
void Queue<ElemType>::Clear()
{
	size=0;
}
