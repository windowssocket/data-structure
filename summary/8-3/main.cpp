#include <iostream>
using namespace std;

//Ҫ����ඨ��
template <class Type>
class BinarySearchTree
{
private:
	struct BinaryNode //�洢�ṹ
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

	bool find(const Type &x) const;		//��������������������
	void insert(const Type &x);
	void remove(const Type &x);

	void remove_less_than_k(const Type &x) { remove_less_than_k(x,root); }			// ɾ������С��ĳ��ָ��ֵ������Ԫ�ذ�������
	void remove_greater_than_k(const Type &x) { remove_greater_than_k(x,root); }	// ɾ�����д���ĳ��ָ��ֵ������Ԫ�ذ�������
	void remove_range(const Type &x1, const Type &x2) { remove_range(x1,x2,root);}	// ɾ�����д���ĳ��ָ��ֵ������Ԫ�ذ�������

	Type find_kth(unsigned i)	// ���ҵ�k��Ԫ��
	{
		flag=0;
		return find_kth(i,root);
	}

private:
	BinaryNode *root;
	int flag;
	void output(BinaryNode *t);								//���ʵ��
	void insert(const Type &x, BinaryNode* &t);				//����Ԫ��ʵ��
	void remove(const Type &x, BinaryNode* &t);				//ɾ������ʵ��
	bool find (const Type &x, BinaryNode *t) const;			//���Һ���ʵ��
	void makeEmpty(BinaryNode* &t);
	void remove_less_than_k(const Type &x, BinaryNode *t);									// ����ʵ��
	void remove_greater_than_k(const Type &x, BinaryNode *t);								// ����ʵ��
	void remove_range(const Type &x1, const Type &x2, BinaryNode *t);						// ����ʵ��
	Type find_kth(int i, BinaryNode *t);					//���ҵ�k��Ԫ��
	BinaryNode* getfather(BinaryNode *x,BinaryNode *t)		//���ҵ�ǰ���ĸ��׽��
	{
		if (root==x) return NULL;
		if (t->left==x) return t;
		if (t->right==x) return t;
		if (t->data>x->data) return getfather(x,t->left);
		else return getfather(x,t->right);
	}
};

//���ֺ�����ʵ��
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

//�ǵݹ�ʵ��
template <class Type>
bool BinarySearchTree<Type>::find(const Type &x, BinaryNode *p) const //�ǵݹ�
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
void BinarySearchTree<Type>::insert(const Type &x, BinaryNode* &t)//�ǵݹ�,�õ���
{
	BinaryNode *f,*p;
	if (t==NULL)
	{
		t=new BinaryNode(x,NULL,NULL);
		return;
	}
	p=t;
	while (p!=NULL)						//���Һ��ʵĲ���λ��
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
	if (x<f->data)						//�����µ�Ԫ��
		f->left=new BinaryNode(x,NULL,NULL);
	else f->right=new BinaryNode(x,NULL,NULL);
}

template <class Type>
void BinarySearchTree<Type>::remove(const Type &x)
{
	remove(x,root);
}


template<class Type>
void BinarySearchTree<Type>::remove(const Type &x, BinaryNode* &t)//�ǵݹ�
{
	BinaryNode *p=t;
	BinaryNode *q,*s;
	BinaryNode *f=NULL;
	while(p!=NULL)												//���ҷ��ϵ�Ԫ��λ��
	{
		if(p->data==x)
		{
			if(!p->right)			//ֻ�������
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
				if(!p->left)	//ֻ���Ҷ���
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
				else			//û�ж��ӵ����
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

//ɾ������Ҫ�������ֵ(��������ĳֵ,С��ĳֵ��һ��������)
template <class Type>
void BinarySearchTree<Type>::remove_less_than_k(const Type &x, BinaryNode *t)
{
	BinaryNode *fa;
	Type tmp;
	if (t==NULL) return;
	while (t->data<x)			//��һ������ϲ���ɾ������Ҫ��ĵ�,Ȼ�����������������ͬ����
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
	while (t->data>x) //��һ������ϲ���ɾ������Ҫ��ĵ�,Ȼ�����������������ͬ����
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
	while (t->data>=x1 && t->data<x2) //��һ������ϲ���ɾ������Ҫ��ĵ�,Ȼ�����������������ͬ����
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

//���ҵ�k��Ԫ�ص�
template <class Type>
Type BinarySearchTree<Type>::find_kth(int i, BinaryNode *t)
{
	int tmp;
	if (t!=NULL)					//�������������˳�����ɨ��,���ҵ���k��ʱֹͣ
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
    cout<<"����ԭ��Ԫ�أ�";
    tree.output();
    cout<<endl;
    tree.remove(2);
    cout<<tree.find(2)<<"����ɾ��2��û���ҵ�2"<<endl;
    cout<<"ɾ��2������Ԫ�أ�";
    tree.output();
    cout<<endl;
    tree.find_kth(4);
    tree.remove_less_than_k(4);
    cout<<"ɾ����4С��Ԫ�غ�����Ԫ�أ�";
    tree.output();
    cout<<endl;
    tree.remove_greater_than_k(7);
    cout<<"ɾ����7���Ԫ�غ�����Ԫ�أ�";
    tree.output();
    cout<<endl;
    tree.remove_range(4,6);
    cout<<"ɾ����4���6С��Ԫ�غ�����Ԫ�أ�";
    tree.output();
    cout<<endl;                             //test for problem 8.9
    cout<<"test is successful"<<endl;
}
