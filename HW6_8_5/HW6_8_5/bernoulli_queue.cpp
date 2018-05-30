#include"bernoulli_queue.h"

template<class Type>
void bernoulli_queue<Type>::clearTree(Node* t) //using recursion to delete tree
{
	if(t!=NULL){
		clearTree(t->son);
		clearTree(t->brother);
		delete t;
	}
}

template<class Type>
void bernoulli_queue<Type>::clear()  //only clear each BnlTree but not the array 
{
	for(int i=0; i<length; ++i){
		clearTree(root[i]);
		root[i]=NULL;
	}
	nodeSize=0;
}

template<class Type>
bernoulli_queue<Type>::bernoulli_queue(const bernoulli_queue &R)
{
	if(this==&R) return;
	else{
		root=new BnlTree[R.length];
		for(int i=0; i<R.length; ++i) root[i]=copyTree(R.root[i]);  //copy every tree deeply
		length=R.length;
		nodeSize=R.nodeSize;
	}
}

template<class Type>
void bernoulli_queue<Type>::doubleSpace()  //double the length of the array
{
	BnlTree *tmp=new BnlTree[2*length];
	for(int i=0; i<length; ++i) tmp[i]=root[i];
	for(int i=length; i<2*length; ++i) tmp[i]=NULL;
	length*=2;
	root=tmp;
}

template<class Type>
const Type& bernoulli_queue<Type>::top() const
{
	int min=-1;
	for(int i=0; i<length; ++i)       //find the min node
		if(root[i]!=NULL && (min==-1 || root[min]->data>root[i]->data)) min=i;
	
	return root[min]->data;
}

template<class Type>
bernoulli_queue<Type> bernoulli_queue<Type>::operator+(const bernoulli_queue &R) const
{
	bernoulli_queue sun(*this);
	while(sun.length<=R.length) sun.doubleSpace();
	if(sun.root[sun.length-1]!=NULL) sun.doubleSpace();  //because the last node maybe carried 

	Node* tmp;
	for(int i=0; i<R.length; ++i){   //take every BnlTree from R one-by-one
		if(R.root[i]!=NULL){
			tmp=copyTree(R.root[i]);
			int j;
			for(j=i; sun.root[j]!=NULL; ++j){    //consider carry
				tmp=linkTree(tmp,sun.root[j]);   //link two BnlTrees to one
				sun.root[j]=NULL;
			}
			sun.root[j]=tmp;
		}
	}
	sun.nodeSize+=R.nodeSize;
	return sun;
}

template<class Type>
bernoulli_queue<Type>& bernoulli_queue<Type>::operator =(const bernoulli_queue &R)
{
	if(this==&R) return *this;
	else{
		clearQueue(); //destruct the capacity before
		root=new BnlTree[R.length];
		for(int i=0; i<R.length; ++i) root[i]=copyTree(R.root[i]);
		length=R.length;
		nodeSize=R.nodeSize;
		return *this;
	}
}

template<class Type>
void bernoulli_queue<Type>::push(const Type &x)
{
	bernoulli_queue R(x);
	*this=*this+R;
}

template<class Type>
void bernoulli_queue<Type>::pop()
{
	int min=-1,tmpSize=nodeSize;
	for(int i=0; i<length; ++i)
		if(root[i]!=NULL && (min==-1 || root[min]->data>root[i]->data)) min=i;  //find the min node
	
	Node *tmp=root[min]->son;
	root[min]=NULL;
	
	//Bn tree is divided into B0,B1,B2,...Bn-1
	//wo only need to add up {B0,B1,..Bn-1} to *this
	if(min!=0){
		bernoulli_queue R;
		R.clearQueue();
		R.length=min;
		R.root=new BnlTree[min];
		for(int i=0; i<R.length; ++i){
			R.root[i]=tmp;
			tmp=tmp->brother;
			R.root[i]->brother=NULL;
		}
		*this=*this+R;
	}
	nodeSize=tmpSize-1;
}