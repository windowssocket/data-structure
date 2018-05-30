#include"bernoulli_queue.h"
#include"bernoulli_queue.cpp"

int main()
{
	bernoulli_queue<int> B,C,D,E;
	for(int i=78; i!=0; i-=2) B.push(i);
	for(int i=79; i>0; i-=2) C.push(i);
	D=B+C;
	cout<<B.size()<<endl;
	D.pop();
	D.clear();
	E=B+D;
	cout<<E.size()<<endl;
	while(!E.empty()){
		cout<<E.top()<<endl;
		E.pop();
	}
}