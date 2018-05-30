#include<iostream>
using namespace std;

int Ackerman(int m, int n) //using recursion, it is easy
{
	if(m==0) return n+1;
	else if(n==0) return Ackerman(m-1,1);
	else return Ackerman(m-1,Ackerman(m,n-1));
}

void main()
{
	int m,n;
	cout<<"please input m,n:";
	cin>>m>>n;
	cout<<"A("<<m<<','<<n<<")="<<Ackerman(m,n)<<endl;
}