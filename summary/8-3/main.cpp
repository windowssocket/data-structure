#include <iostream>
using namespace std;

//要求的类定义
template <class Type>
class BinarySearchTree
{
private:
	struct BinaryNode //存储结构
	{
		Type data;
		BinaryNode *left, *right;
		BinaryNode(const Type &thedata, BinaryNode *lt, BinaryNode *rt)
			:data(thedata),left(lt),right(rt){}
	};
public:
	BinarySearchTree(BinaryNode *t=NULL) {root=t;}
	~BinarySearchTree() {};

	void output()
	{
		output(root);
	}

	bool find(const Type &x) const;		//三个基本函数包裹函数
	void insert(const Type &x);
	void remove(const Type &x);

	void remove_less_than_k(const Type &x) { remove_less_than_k(x,root); }			// 删除树中小于某个指定值的所有元素包裹函数
	void remove_greater_than_k(const Type &x) { remove_greater_than_k(x,root); }	// 删除树中大于某个指定值的所有元素包裹函数
	void remove_range(const Type &x1, const Type &x2) { remove_range(x1,x2,root);}	// 删除树中大于某个指定值的所有元素包裹函数

	Type find_kth(unsigned i)	// 查找第k大元素
	{
		flag=0;
		return find_kth(i,root);
	}

private:
	BinaryNode *root;
	int flag;
	void output(BinaryNode *t);								//输出实现
	void insert(const Type &x, BinaryNode* &t);				//插入元素实现
	void remove(const Type &x, BinaryNode* &t);				//删除函数实现
	bool find (const Type &x, BinaryNode *t) const;			//查找函数实现
	void makeEmpty(BinaryNode* &t);
	void remove_less_than_k(const Type &x, BinaryNode *t);									// 函数实现
	void remove_greater_than_k(const Type &x, BinaryNode *t);								// 函数实现
	void remove_range(const Type &x1, const Type &x2, BinaryNode *t);						// 函数实现
	Type find_kth(int i, BinaryNode *t);					//查找第k个元素
	BinaryNode* getfather(BinaryNode *x,BinaryNode *t)		//查找当前结点的父亲结点
	{
		if (root==x) return NULL;
		if (t->left==x) return t;
		if (t->right==x) return t;
		if (t->data>x->data) return getfather(x,t->left);
		else return getfather(x,t->right);
	}
};

//各种函数的实现
template <class Type>
void BinarySearchTree<Type>::output(BinaryNode *p)
{
	if (p==NULL) return;
	output(p->left);
	cout << p->data << ' ';
	output(p->right);
}

template <class Type>
bool BinarySearchTree<Type>::find(const Type &x) const
{
	return find (x,root);
}

//非递归实现
template <class Type>
bool BinarySearchTree<Type>::find(const Type &x, BinaryNode *p) const //非递归
{
	while ((p!=NULL))
	{
		if (x<p->data)
		{
			p=p->left;
			continue;
		}
		if (p->data<x)
		{
			p=p->right;
			continue;
		}
		if (p->data==x)
			return true;
	}
	return false;
}

template <class Type>
void BinarySearchTree<Type>::insert(const Type &x)
{
	insert(x,root);
}

template <class Type>
void BinarySearchTree<Type>::insert(const Type &x, BinaryNode* &t)//非递归,用迭代
{
	BinaryNode *f,*p;
	if (t==NULL)
	{
		t=new BinaryNode(x,NULL,NULL);
		return;
	}
	p=t;
	while (p!=NULL)						//查找合适的插入位置
	{
		if (x<p->data)
		{
			f=p;
			p=p->left;
		}
		else
		{
			f=p;
			p=p->right;
		}
	}
	if (x<f->data)						//插入新的元素
		f->left=new BinaryNode(x,NULL,NULL);
	else f->right=new BinaryNode(x,NULL,NULL);
}

template <class Type>
void BinarySearchTree<Type>::remove(const Type &x)
{
	remove(x,root);
}


template<class Type>
void BinarySearchTree<Type>::remove(const Type &x, BinaryNode* &t)//非递归
{
	BinaryNode *p=t;
	BinaryNode *q,*s;
	BinaryNode *f=NULL;
	while(p!=NULL)												//查找符合的元素位置
	{
		if(p->data==x)
		{
			if(!p->right)			//只有左儿子
			{
				if(p==t)
				{t=t->left;delete p;}
				else
				{
					q=p;
					if(f->right==p)
						f->right=p->left;
					else f->left=p->left;
					delete q;
				}
			}
			else
				if(!p->left)	//只有右儿子
				{
					if(p==t)
					{ t=t->right; delete p;}
					else
					{
						q=p;
						if(f->left==p)
							f->left=p->right;
						else f->right=p->right;
						delete q;
					}
				}
				else			//没有儿子的情况
				{
					q=p;
					s=p->left;
					while(s->right)
					{q=s;s=s->right;}
					p->data=s->data;
					if(p!=q)
						q->right=s->left;
					else  q->left=s->left;
				}
				break;
		}
		else if(p->data>x)
		{f=p;p=p->left;}
		else
		{f=p;p=p->right;}
	}

	if(p==NULL)  return;
}

//删除满足要求的所有值(包括大于某值,小于某值和一定区间内)
template <class Type>
void BinarySearchTree<Type>::remove_less_than_k(const Type &x, BinaryNode *t)
{
	BinaryNode *fa;
	Type tmp;
	if (t==NULL) return;
	while (t->data<x)			//在一个结点上不断删除符合要求的点,然后对左右子树进行相同操作
	{
		tmp=t->data;
		fa=getfather(t,root);
		remove(t->data,root);
		if (fa==NULL)
		{
			t=root;
			if (t==NULL) return;
			continue;
		}
		if (tmp>fa->data) t=fa->right;
		else t=fa->left;
		if (t==NULL) return;
	}
	remove_less_than_k(x,t->left);
	remove_less_than_k(x,t->right);
}

template <class Type>
void BinarySearchTree<Type>::remove_greater_than_k(const Type &x, BinaryNode *t)
{
	BinaryNode *fa;
	Type tmp;
	if (t==NULL) return;
	while (t->data>x) //在一个结点上不断删除符合要求的点,然后对左右子树进行相同操作
	{
		tmp=t->data;
		fa=getfather(t,root);
		remove(t->data,root);
		if (fa==NULL)
		{
			t=root;
			if (t==NULL) return;
			continue;
		}
		if (tmp>fa->data) t=fa->right;
		else t=fa->left;
		if (t==NULL) return;
	}
	remove_greater_than_k(x,t->right);
	remove_greater_than_k(x,t->left);
}

template <class Type>
void BinarySearchTree<Type>::remove_range(const Type &x1, const Type &x2, BinaryNode *t)
{
	BinaryNode *fa;
	Type tmp;
	if (t==NULL) return;
	while (t->data>=x1 && t->data<x2) //在一个结点上不断删除符合要求的点,然后对左右子树进行相同操作
	{
		tmp=t->data;
		fa=getfather(t,root);
		remove(t->data,root);
		if (fa==NULL)
		{
			t=root;
			if (t==NULL) return;
			continue;
		}
		if (tmp>fa->data) t=fa->right;
		else t=fa->left;
		if (t==NULL) return;
	}
	remove_range(x1,x2,t->left);
	remove_range(x1,x2,t->right);
}

//查找第k个元素的
template <class Type>
Type BinarySearchTree<Type>::find_kth(int i, BinaryNode *t)
{
	int tmp;
	if (t!=NULL)					//利用中序遍历的顺序进行扫描,查找到第k个时停止
	{
		tmp=find_kth(i,t->left);
		if (flag==i) return tmp;
		flag++;
		if (flag==i) return t->data;
		tmp=find_kth(i,t->right);
		if (flag==i) return tmp;
	}
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
    cout<<"树中原有元素：";
    tree.output();
    cout<<endl;
    tree.remove(2);
    cout<<tree.find(2)<<"代表删除2后没有找到2"<<endl;
    cout<<"删除2后树中元素：";
    tree.output();
    cout<<endl;
    tree.find_kth(4);
    tree.remove_less_than_k(4);
    cout<<"删除比4小的元素后树中元素：";
    tree.output();
    cout<<endl;
    tree.remove_greater_than_k(7);
    cout<<"删除比7大的元素后树中元素：";
    tree.output();
    cout<<endl;
    tree.remove_range(4,6);
    cout<<"删除比4大比6小的元素后树中元素：";
    tree.output();
    cout<<endl;                             //test for problem 8.9
    cout<<"test is successful"<<endl;
}
