#include"Simulator.h"

void main()
{
	double interval,p,time;
	
	cout<<"��������Ҫģ�����ʱ��: ";
	cin>>time;
	
	Simulator test(time);
	
	cout<<"������Լÿ������ʱ����һ����: ";
	cin>>interval;
	cout<<"�����������ͳ��ĳ��ֱ�����1�ȼ�: ";
	cin>>p;
	cout<<endl;
	test.avgWaitTime(interval*2,p);
	cout<<endl;
}