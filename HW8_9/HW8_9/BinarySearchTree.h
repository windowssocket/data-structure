#ifndef _BinarySearchTree_h_
#define _BinarySearchTree_h_

#include<iostream>
using namespace std;

template<typename Type>
class BinarySearchTree
{
private:
	struct node{
		Type data;
		node *left,*right;
		node():left(NULL),right(NULL){}
		node(Type x):data(x),left(NULL),right(NULL){}
	};
	node *root;

	void clear(node *t);
	void output(node *t);
	bool find_kth(node *t, unsigned int &k, Type &value);

public:
	BinarySearchTree():root(NULL){}
	~BinarySearchTree(){clear(root);}
	
	// ���º�������ʹ�õݹ�ʵ�֣�����Ҫ����<<�����	
	void output(); // ʹ�������������������е�����

	// ��������������ʹ�÷ǵݹ�ʵ�֣������ܵ÷�
	void insert(const Type &); // ��һ��ֵ���뵽�����������
	void remove(const Type &);// ɾ������������е���ָ��ֵ��Ԫ��
	bool find(const Type &); // ����ָ��ֵ��Ԫ���Ƿ�����ڶ����������

	// ���¼��������ٶ�Type����֧�����бȽϴ�С����������뾡��ֻʹ��С�ںź͵��ںţ�
	Type find_kth(unsigned int k){Type x; find_kth(root,k,x); return x;} // ���ҵ�k��Ԫ��
	void remove_less_than_k(const Type &); // ɾ������С��ĳ��ָ��ֵ������Ԫ��
	void remove_greater_than_k(const Type &); //ɾ�����д���ĳ��ָ��ֵ������Ԫ��
	void remove_range(const Type &x, const Type &y); // ɾ������ҿ�����[x, y)�е�����Ԫ��
};


template<typename Type>
void BinarySearchTree<Type>::clear(node *t)    //using recursion to clear node
{
	if(t!=NULL){
		if(t->left!=NULL) clear(t->left);
		if(t->right!=NULL) clear(t->right);
		delete t;
	}
}

template<typename Type>
void BinarySearchTree<Type>::output(node *t)   //using recursion to clear node
{
	if(t!=NULL){
		output(t->left);
		cout<<t->data<<' ';
		output(t->right);
	}
}

template<typename Type>
void BinarySearchTree<Type>::output()
{
	if(root==NULL) cout<<"empty"<<endl;
	else{
		output(root);
		cout<<endl;
	}
}

template<typename Type>
void BinarySearchTree<Type>::insert(const Type &x)
{
	node **p=&root;  //p is a pointer point to *node
	while(*p!=NULL){
		if(x<(*p)->data) p=&(*p)->left;
		else p=&(*p)->right;
	}
	*p=new node(x);
}

template<typename Type>
void BinarySearchTree<Type>::remove(const Type &x)
{
	node **p=&root;
	while(*p!=NULL){
		if(x<(*p)->data) p=&(*p)->left;
		else if(!(x==(*p)->data)) p=&(*p)->right;   //ʵ������ x!=(*p)->data, ��Ϊ��ֻ��С�ڵ��ںž�ֻ����ôд��
		else{   //find x
			node *rt=(*p)->left,*tmp=*p;
			for(*p=(*p)->right; *p!=NULL; p=&(*p)->left);  //find the min node in right tree
			*p=rt;
			delete tmp;
		}
	}
}

template<typename Type>
bool BinarySearchTree<Type>::find(const Type &x)
{
	node *p=root;
	while(p!=NULL){
		if(x==p->data) return true;
		else if(x<p->data) p=p->left;
		else p=p->right;
	}
	return false;
}

template<typename Type>
bool BinarySearchTree<Type>::find_kth(node *t, unsigned int &k, Type &value)  //using mid-post tranverse to find the kth elem
{
	if(t!=NULL){
		if(find_kth(t->left,k,value)) return true;
		if(--k==0){
			value=t->data;
			return true;
		}
		if(find_kth(t->right,k,value)) return true;
	}
	return false;
}

template<typename Type>
void BinarySearchTree<Type>::remove_less_than_k(const Type &x)
{
	node **p=&root;
	while(*p!=NULL){
		if(x<(*p)->data || x==(*p)->data) p=&(*p)->left;   //try to reach the node less than x
		else{
			node *tmp=*p;
			*p=(*p)->right;    //the 'root' node point to the next
			tmp->right=NULL;
			clear(tmp);
		}
	}
}

template<typename Type>
void BinarySearchTree<Type>::remove_greater_than_k(const Type &x)
{
	node **p=&root;
	while(*p!=NULL){
		if((*p)->data<x || x==(*p)->data) p=&(*p)->right;  //try to reach the node greater than x
		else{
			node *tmp=*p;
			*p=(*p)->left;   //the 'root' node point to the next
			tmp->left=NULL;
			clear(tmp);
		}
	}
}

template<typename Type>
void BinarySearchTree<Type>::remove_range(const Type &x, const Type &y)
{
	node *rt=root, **p=&rt, **r=&root;
	while((*p)!=NULL){      //separate the tree from two part
		if((*p)->data<x){
			*r=(*p)->right;
			p=&(*p)->right;
		}
		else{
			r=&(*r)->left;
			*p=(*p)->left;
		}
	}
	remove_less_than_k(y);  //deal with the right part
	//link two part to one
	*p=root;
	root=rt;
}

#endif