#include"BinarySearchTree.h"
#include<string>
using namespace std;

int main()
{
	BinarySearchTree<int> B;
	B.insert(3);
	B.insert(2);
	B.insert(1);
	B.remove_range(1,2);
	B.output();
	/*
	string c;
	cin>>c;
	while(c!="N"){
		if(c=="i"){
			char x; cin>>x; B.insert(x);
		}
		if(c=="r"){
			char x; cin>>x; B.remove(x);
		}
		if(c=="f"){
			char x; cin>>x; cout<<B.find(x)<<endl;
		}
		if(c=="fth"){
			int k; cin>>k; cout<<B.find_kth(k)<<endl;
		}
		if(c=="rs"){
			char x; cin>>x; B.remove_less_than_k(x);
		}
		if(c=="rb"){
			char x; cin>>x; B.remove_greater_than_k(x);
		}
		if(c=="rr"){
			char x,y;cin>>x>>y;B.remove_range(x,y);
		}
		B.output();
		cin>>c;
	}
	*/
	return 0;
}