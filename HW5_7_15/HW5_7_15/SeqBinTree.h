#ifndef _SeqBinTree_h_
#define _SeqBinTree_h_

#include<iostream>
#include<queue>
using namespace std;

template<class Type>
class SeqBinTree{
private:
	struct Node{
		Type data;
		int left;
		int right;

		Node(){left=right=-1;}
	};

	Node *tree;  //save the tree node
	int length;
	int maxSize;

	void DoubleSize();
	void Assign(Type x, int i);  //assign x to tree[i], it also lead the length +1
	int Height(int i,Node *t)const;
	void PreOrder(int i,Node *t);
	void MidOrder(int i,Node *t);
	void PostOrder(int i,Node *t);

public:
	SeqBinTree(){tree=new Node[2];maxSize=2;length=0;}
	~SeqBinTree(){delete[] tree;}
	
	void Clear(){length=0;}
	void Create();
	bool IsEmpty()const{return length==0;}
	int Size()const{return length;}
	int Height()const{ return Height(0,tree);}
	void PreOrder();
	void MidOrder();
	void PostOrder();

};

#endif