#include"IntQueue.h"

void IntQueue::doubleSpace()
{
	int *tmp=new int[maxSize*=2];
	for(int i=1; i<=currentSize; ++i) tmp[i]=elem[i];
	delete[] elem;
	elem=tmp;
}

void IntQueue::percolateDown(int hole)  //top-down filtering
{
	int child,x=elem[hole];
	while(2*hole<=currentSize){
		child=hole*2;
		if(child+1<=currentSize && elem[child]>elem[child+1]) ++child;
		if(x>elem[child]) elem[hole]=elem[child];
		else break;
		hole=child;
	}
	elem[hole]=x;
}

void IntQueue::enQueue(int x)
{
	if(++currentSize==maxSize) doubleSpace();  //assign more space for the array

	int i;
	for(i=currentSize; i>1; i/=2)
		if(elem[i/2]>x) elem[i]=elem[i/2];
		else break;
	elem[i]=x;
}

void IntQueue::CreateTree()
{
	int n,x;
	cout<<"请输入你要输入的元素个数：";
	cin>>n;
	cout<<"请输入该优先队列："<<endl;
	for(int i=0; i<n; ++i){
		cin>>x;
		enQueue(x);
	}
}

void IntQueue::deQueue()
{
	elem[1]=elem[currentSize--];
	percolateDown(1);
}

int IntQueue::findMin(int x)
{
	int min,index=0;
	for(int i=1; i<=currentSize; ++i){
		if(index!=0){    //the value larger than x has occured
			if(elem[i]>x && elem[i]<min){
				min=elem[i];
				index=i;
			}
		}
		else{           //the value larger than x has not occured
			if(elem[i]>x){
				min=elem[i];
				index=i;
			}
		}
	}
	return index;
}

void IntQueue::decreaseKey(int i, int value)
{
	elem[i]-=value;
	while(i!=1 && elem[i]<elem[i/2]){   //if value>0 then down-top filtering
		swap(elem[i],elem[i/2]);
		i/=2;
	}

	int child,tmp=elem[i];
	while(2*i<=currentSize){   //if value<0 then top-down filtering
		child=i*2;
		if(child+1<=currentSize && elem[child]>elem[child+1]) ++child;
		if(tmp>elem[child]) elem[i]=elem[child];
		else break;
		i=child;
	}
	elem[i]=tmp;
}
