#include"GH_Queue.h"
#include"GH_Queue.cpp"
#include<iostream>
using namespace std;


void Build(Queue<int> &q,int maxSize)
{
	int size,elem;
	cout<<"Please input the queue size(max size of the queue is "<<maxSize<<"):"<<endl;
	
	do
	{
		cin>>size;
		if(size>10) cout<<"This size is too large, please reply:"<<endl; //input safely
		if(size<1) cout<<"This size is illegal, please reply:"<<endl; //input safely
	
	}while(size>maxSize || size<1);

	for(int i=0; i<size; ++i)
	{
		cout<<"Please input an integer to fill the queue: ";
		cin>>elem;
		q.Enqueue(elem);
	}
}


void Append(Queue<int> &q)
{
	int x;

	if(q.IsFull()) cout<<"the queue is full, you can't append elem"<<endl;
	else
	{
		cout<<"please input an integer you want to append to the queue:";
		cin>>x;
		q.Enqueue(x);
	    q.Display();
	}
}


void Remove(Queue<int> &q)
{
	if(q.GetSize()==0) cout<<"The queue is empty, you can't remove any elem"<<endl;
	else
	{
		cout<<"This is Dequeue operation:"<<q.Dequeue()<<endl;
		q.Display();
	}

}


void Locate(Queue<int> &q)
{
	int i;

	if(q.GetSize()==0) cout<<"the queue is empty"<<endl;
	else
	{
		cout<<"Input the index you want to locate:";
		do
		{
			cin>>i;
			if(i>=q.GetSize()) cout<<"This index is beyond the size, please reply:"; //input safely
			if(i<0) cout<<"This index is illegal, please reply:"; //input safely
	
		}while(i>=q.GetSize() || i<0);

		cout<<"the index "<<i<<" elem in queue is:"<<q.Peek(i)<<endl;
	}
}


void Clear(Queue<int> &q)
{
	q.Clear();
	cout<<"the queue is cleared"<<endl;
}



void main()
{
	int mode,maxSize=10;
	Queue<int> q(maxSize);

	Build(q,maxSize);
	q.Display();
	do
	{
		cout<<endl<<"******************************************************************"<<endl;
		cout<<"Select the mode you need"<<endl
			<<"<1:Display 2:Append 3:Remove 4:Locate 5:Clear /default:exit>:";
		cin>>mode;
		cout<<"_________________________________________________________"<<endl<<endl;

		switch(mode)
		{
			case 1: q.Display();break;
			case 2: Append(q);break;
			case 3: Remove(q);break;
			case 4: Locate(q);break;
			case 5: Clear(q);break;
			default: cout<<"Thank you for using class Queue"<<endl; return;
		}

	}while(true);

}