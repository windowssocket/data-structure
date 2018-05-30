#include"seqList.h"
#include"seqList.cpp"

int main()
{
	seqList<int> A,B,C;
	cout<<"please input A ,input 0 to end:"<<endl;
	A.input(0);
	cout<<"please input B ,input 0 to end:"<<endl;
	B.input(0);
	cout<<"\nA=";A.traverse();
	cout<<"\nB=";B.traverse();
	cout<<"\nA+B=";
	C=A+B;
	C.traverse();
	cout<<endl;
}