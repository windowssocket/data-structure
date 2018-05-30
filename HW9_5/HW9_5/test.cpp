#include"hashTable.h"
#include"closeHashTable.h"
template<class Type>
int f(const Type &x){
	return int(x);
}

int main(){
	closeHashTable<char> h(1,f);
	int x;
	do{
		char tmp;
		cin>>x;
		switch(x){
		case 0: cin>>tmp; h.insert(tmp);break;
		case 1: cin>>tmp; h.remove(tmp);break;
		case 3: cin>>tmp; cout<<h.find(tmp)<<endl; break;
		}
		for(char a='a'; a<='z'; ++a) if(h.find(a)) cout<<a<<' ';
		cout<<endl;
	}while(x!=4);
	return 0;
}