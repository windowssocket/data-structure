#include"IntQueue.h"

int main()
{
	IntQueue Q;
	Q.CreateTree();
	
	int x,value;
	cout<<"x��value��(�㶮�ģ�";
	cin>>x>>value;
	
	Q.decreaseKey(Q.findMin(x),value);
	
	cout<<"�����˱� "<<x<<" ����� "<<value<<" �����ȼ��� ����Ϊ:"<<endl;
	while(!Q.isEmpty()) {cout<<Q.getHead()<<' '; Q.deQueue();}
	cout<<endl;
	return 0;
}