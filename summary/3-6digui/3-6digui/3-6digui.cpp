#include <iostream>
using namespace std;

//利用递归方法实现
int Ackerman(int a,int b);

int main()
{
	int m,n;
	cout<<"请输入函数第一个参量m的值: m=";
	cin>>m;
	cout<<"请输入函数第二个参量n的值: n=";
	cin>>n;
	cout<<"函数值为"<<Ackerman(m,n)<<endl;
	system("pause");
}

int Ackerman(int a,int b)
{
	if(a==0) return(b+1);
	else if(a!=0&&b==0) return (Ackerman(a-1,1));
	else if(a!=0&&b!=0) return (Ackerman(a-1,Ackerman(a,b-1)));
}
