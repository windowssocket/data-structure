#include"adjListGraph.h"

int main()
{
	int d[20]={1,2,3,4,5,6,7,8,9,10};
	adjListGraph G(10,d);
	G.insert(1,2,3);
	G.insert(2,3,1);
	G.insert(1,3,4);
	G.insert(4,5,0);
	cout<<G.find(1,4)<<endl;
	return 0;
}