#include"IntQueue.h"

int main()
{
	IntQueue Q;
	Q.CreateTree();
	
	int x,value;
	cout<<"x？value？(你懂的）";
	cin>>x>>value;
	
	Q.decreaseKey(Q.findMin(x),value);
	
	cout<<"减少了比 "<<x<<" 大的数 "<<value<<" 的优先级后 队列为:"<<endl;
	while(!Q.isEmpty()) {cout<<Q.getHead()<<' '; Q.deQueue();}
	cout<<endl;
	return 0;
}