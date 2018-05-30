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
	void removeless(const Type &x) { removeless(x,root); }
	void removelarger(const Type &x) { removelarger(x,root); }
	void removebetween(const Type &x1, const Type &x2) { removebetween(x1,x2,root); }

private:
	BinaryNode *root;
	void insert(const Type &x, BinaryNode* &t);
	void remove(const Type &x, BinaryNode* &t);
	bool find (const Type &x, BinaryNode *t) const;
	void removeless(const Type &x, BinaryNode* &t);
	void removelarger(const Type &x, BinaryNode* &t);
	void removebetween(const Type &x1, const Type &x2, BinaryNode* &t);
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
	else if (x<t->data)
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
	else if (t->left!=NULL && t->right!=NULL)   //有两个儿子
	{
		BinaryNode *tmp=t->right;
		while (tmp->left!=NULL) tmp=tmp->left;
		t->data=tmp->data;   //用右子树最小节点作为替身
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
void BinarySearchTree<Type>::removeless(const Type &x, BinaryNode* &t)
{
	if (t==NULL) return;
	while(t->data<x)
	{
		remove(t->data,t);
	}  //如果t的值比x小，不停地删除它
	removeless(x,t->left);  //删除t左子树所有元素
	if (t->right!=NULL)
		if (t->right->data<x) removeless(x,t->right);  //如果右子树还有元素并且比x小，删除它
}

template <class Type>
void BinarySearchTree<Type>::removelarger(const Type &x, BinaryNode* &t)
{
    if (t==NULL) return;
	while(t->data>x)
	{
		remove(t->data,t);
	}  //如果t的值比x大，不停地删除它
	removelarger(x,t->right);  //删除t右子树所有元素
	if (t->left!=NULL)
		if (t->left->data>x) removeless(x,t->left);  //如果左子树还有元素并且比x大，删除它
}

template <class Type>
void BinarySearchTree<Type>::removebetween(const Type &x1, const Type &x2, BinaryNode* &t)
{
	if (t==NULL) return;
	if((t->data>x1) && (t->data<x2)) remove(t->data,t);
	removebetween(x1,x2,t->left);
	removebetween(x1,x2,t->right);  //全方位搜索在x1到x2范围内的值并且删除它
}

int main()
{
	BinarySearchTree<int> tree;
    tree.insert(7);
    tree.insert(8);
    tree.insert(6);
    tree.insert(3);
    tree.insert(4);
    tree.insert(10);
    tree.insert(9);
    tree.insert(5);
    tree.insert(1);
    tree.insert(2);
    tree.removeless(2);
	if (tree.find(1)) cout <<"进行删除比2小的值的操作后，能找到1\n";
	else cout <<"进行删除比2小的值的操作后，不能找到1\n";
    tree.removelarger(9);
    if (tree.find(10)) cout <<"进行删除比9大的值的操作后，能找到10\n";
	else cout <<"进行删除比9大的值的操作后，不能找到10\n";
	tree.removebetween(7,9);
	if (tree.find(8)) cout <<"进行删除比7大比9小的值的操作后，能找到8\n";
	else cout <<"进行删除比7大比9小的值的操作后，不能找到8\n";
	cout << endl;
}
