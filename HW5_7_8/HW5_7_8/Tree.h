#ifndef _tree_h
#define _tree_h

#include<iostream>
#include<queue>
using namespace std;

template<class Type>
class Tree{
private:
	struct Node{
		Node *son,*brother;  //left-child is son while right-child is brother 
		Type data;

		Node():left(NULL),right(NULL){}
		Node(Type item, Node *S=NULL, Node *B=NULL):data(item),son(S),brother(B){}
		~Node(){}
	};

	Node *root;

	void clear(Node *t){
		if(t->son!=NULL) clear(t->son);
		if(t->brother!=NULL) clear(t->brother);
		delete t;
	}

	void PreOrder(Node *t);
	void PostOrder(Node *t);

public:
	Tree():root(NULL){}
	Tree(const Type &value){root=new Node(value);}
	
	~Tree(){clear();}

	void clear(){if(root!=NULL) clear(root);root=NULL;}

	void CreateTree();
	void PreOrder();
	void PostOrder();
	void LevelOrder();  //using deque

};

#endif