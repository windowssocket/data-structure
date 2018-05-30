#ifndef _List_h_
#define _List_h_

#include<iostream>
using namespace std;

template<class Type>
class List{
private:
	struct node{
		Type data;
		node *next;
		node():next(NULL){}
		node(Type x):data(x),next(NULL){}
	};

	node *head;
	void Delete(node *t){if(t!=NULL){Delete(t->next);delete t;}} //using recursion to destruct head
	void MoveToHead(node* t);  //move the node t->next to the head of the list

public:
	List(){head=new node;}  //using head node
	~List(){Delete(head);}

	void Insert(Type x);
	bool Search(Type x); // 若查找成功返回true否则返回false

	void Traverse();  //traverse the list for testing the promgram

};

#endif
