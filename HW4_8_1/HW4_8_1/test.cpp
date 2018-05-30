#include"Simulator.h"

void main()
{
	double interval,p,time;
	
	cout<<"请输入需要模拟的总时间: ";
	cin>>time;
	
	Simulator test(time);
	
	cout<<"请输入约每隔多少时间来一辆车: ";
	cin>>interval;
	cout<<"请输入货车与客车的出现比例是1比几: ";
	cin>>p;
	cout<<endl;
	test.avgWaitTime(interval*2,p);
	cout<<endl;
}