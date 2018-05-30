#ifndef _binarytree_h
#define _binarytree_h

#include<iostream>
#include<queue>
using namespace std;

template<class Type>
class BinaryTree{
private:
	struct Node{
		Node *left,*right;
		Type data;

		Node():left(NULL),right(NULL){}
		Node(Type item, Node *L=NULL, Node *R=NULL):data(item),left(L),right(L){}
		~Node(){}
	};

	Node *root;

	void clear(Node *t){
		if(t->left!=NULL) clear(t->left);
		if(t->right!=NULL) clear(t->right);
		delete t;
	}

public:
	BinaryTree():root(NULL){}
	BinaryTree(const Type &value){root=new Node(value);}
	
	~BinaryTree(){clear();}

	void clear(){if(root!=NULL) clear(root);root=NULL;}

	void Creat();
	void LevelQrder();  //the add function
	bool IsComplete();  //the add function
		
};

#endif
