#ifndef _closeHashTable_h_
#define _closeHashTable_h_

#include"hashTable.h"

template<class Type>
class closeHashTable:public hashTable<Type>
{
private:
	struct node{
		Type data;   //散列表的结点类
		int state;   //0-empty, 1-active, 2-deleted
		node(){state=0;}
	};
	
	node *elem;
	int size;

public:
	closeHashTable(int length=101, int(*f)(const Type &x)=defaultKey);
	~closeHashTable(){delete[] elem;}
	bool find(const Type &x)const;
	bool insert(const Type &x);
	bool remove(const Type &x);

	void rehash();   //整理散列表
};

template<class Type>
closeHashTable<Type>::closeHashTable(int length, int(*f)(const Type &x))
{
	size=length;
	elem=new node[size];
	key=f;
}

template<class Type>
bool closeHashTable<Type>::find(const Type &x)const
{
	int index=(key(x)%size+size)%size;    //to ensure the index is positive
	for(; elem[index].state!=0; index=(++index)%size)
		if(elem[index].data==x && elem[index].state==1) return true;
	
	return false;
}

template<class Type>
void closeHashTable<Type>::rehash()
{
	node *tmp=elem;     //to save the new hash table
	elem=new node[size];  
	for(int i=0; i<size; ++i) 
		if(tmp[i].state==1) insert(tmp[i].data);
	delete[] tmp;
}

template<class Type>
bool closeHashTable<Type>::insert(const Type &x)
{
	if(find(x)) return true;
	
	int index=(key(x)%size+size)%size;    //to ensure the index is positive
	while(elem[index].state==1) index=(++index)%size;
	elem[index].data=x;
	elem[index].state=1;

	int effect=0;
	for(int i=0; i<size; ++i)
		if(elem[i].state==1) ++effect;
		else --effect;
	
	if(effect>=0){    //need to rehash
		node *tmp=new node[2*size];
		for(int i=0; i<size; ++i) tmp[i]=elem[i];
		delete[] elem;
		elem=tmp;
		size*=2;
		rehash();
	}
	return true;
}

template<class Type>
bool closeHashTable<Type>::remove(const Type &x)
{
	bool isFind=false;
	int index=(key(x)%size+size)%size;    //to ensure the index is positive
	for(; elem[index].state!=0; index=(++index)%size)
		if(elem[index].data==x && elem[index].state==1){
			elem[index].state=3;
			isFind=true;
		}

	if(!isFind) return false;
	else{
		int del=0;    //calulate if the delete node at 50% of the table
		for(int i=0; i<size; ++i)
			if(elem[i].state==3) ++del;
			else --del;
		
		if(del>=0) rehash();  //delete node is more than no del node
		return true;
	}
}


#endif