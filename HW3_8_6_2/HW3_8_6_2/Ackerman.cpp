#include<iostream>
#include<stack>
using namespace std;

int Ackerman(int m,int n)
{
	stack<int> S;  //save m
	int A;

	while(true){
		if(m==0){  //case 1
			A=n+1;
			if(S.empty()) break;
			else{
				m=S.top()-1;
				S.pop();
				n=A;
			}
		}
		else if(n==0){  //case 2
			--m;
			n=1;
		}
		else{    //case 3
			S.push(m);
			--n;
		}
	}

	return A;
}


void main()
{
	int m,n;
	cout<<"please input m,n:";
	cin>>m>>n;
	cout<<"A("<<m<<','<<n<<")="<<Ackerman(m,n)<<endl;
}
