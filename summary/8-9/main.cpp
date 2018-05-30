#include <iostream>
using namespace std;

template <class Type>
class BinarySearchTree
{
private:
	struct BinaryNode
	{
		Type data;
		BinaryNode *left, *right;
		BinaryNode(const Type &thedata, BinaryNode *lt, BinaryNode *rt)
			:data(thedata),left(lt),right(rt){}
	};
public:
	BinarySearchTree(BinaryNode *t=NULL) {root=t;}
	~BinarySearchTree() {}
	bool find(const Type &x) const;
	void insert(const Type &x);
	void remove(const Type &x);
	Type findith(int i)
	{
		flag=0;
		return findith(i,root);
	}

private:
	int flag;
	BinaryNode *root;
	void insert(const Type &x, BinaryNode* &t);
	void remove(const Type &x, BinaryNode* &t);
	bool find (const Type &x, BinaryNode *t) const;
	void makeEmpty(BinaryNode* &t);
	Type findith(int i, BinaryNode *t);
};

template <class Type>
bool BinarySearchTree<Type>::find(const Type &x) const
{
	return find (x,root);
}

template <class Type>
bool BinarySearchTree<Type>::find(const Type &x, BinaryNode *t) const
{
	if (t==NULL)
		return false;
	else if (x<t->data)
		return find(x,t->left);
	else if (t->data<x)
		return find(x,t->right);
	else return true;
}

template <class Type>
void BinarySearchTree<Type>::insert(const Type &x)
{
	insert(x,root);
}

template <class Type>
void BinarySearchTree<Type>::insert(const Type &x, BinaryNode* &t)
{
	if (t==NULL)
		t=new BinaryNode(x,NULL,NULL);
	else if (x < t->data)
		insert(x,t->left);
	else if (t->data<x)
		insert(x,t->right);
}

template <class Type>
void BinarySearchTree<Type>::remove(const Type &x)
{
	remove(x,root);
}

template <class Type>
void BinarySearchTree<Type>::remove(const Type &x, BinaryNode* &t)
{
	if (t==NULL) return;
	if (x<t->data) remove(x,t->left);
	else if (t->data<x) remove(x,t->right);
	else if (t->left!=NULL && t->right!=NULL)
	{
		BinaryNode *tmp=t->right;
		while (tmp->left!=NULL) tmp=tmp->left;
		t->data=tmp->data;
		remove(t->data,t->right);
	}
	else
	{
		BinaryNode *oldNode=t;
		t=(t->left!=NULL)? t->left : t->right;
		delete oldNode;
	}
}

template <class Type>
Type BinarySearchTree<Type>::findith(int i, BinaryNode *t)   //查找第i大元素
{
	if (t!=NULL)
	{
		findith(i,t->right);
		flag++;
		if (flag==i) return t->data;
		findith(i,t->left);
	}
}

int main()
{
	BinarySearchTree<int> tree;
    for(int i=100;i>=1;i--)
        tree.insert(i);
	cout << tree.findith(34) << endl;
}

