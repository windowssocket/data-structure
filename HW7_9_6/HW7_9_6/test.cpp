#include"List.h"
#include"List.cpp"

int main()
{
	int n,x;
	List<int> L;
	cout<<"n?";
	cin>>n;
	for(int i=0; i<n; ++i){
		cin>>x;
		L.Insert(x);
	}

	while(true){
	cout<<"x?";
	cin>>x;
	cout<<L.Search(x)<<endl;
	L.Traverse();
	}

	return 0;
}