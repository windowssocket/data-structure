#include <iostream>
using namespace std;

//���õݹ鷽��ʵ��
int Ackerman(int a,int b);

int main()
{
	int m,n;
	cout<<"�����뺯����һ������m��ֵ: m=";
	cin>>m;
	cout<<"�����뺯���ڶ�������n��ֵ: n=";
	cin>>n;
	cout<<"����ֵΪ"<<Ackerman(m,n)<<endl;
	system("pause");
}

int Ackerman(int a,int b)
{
	if(a==0) return(b+1);
	else if(a!=0&&b==0) return (Ackerman(a-1,1));
	else if(a!=0&&b!=0) return (Ackerman(a-1,Ackerman(a,b-1)));
}
