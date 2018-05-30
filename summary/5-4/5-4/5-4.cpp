#include <iostream>
using namespace std;

//链表队列
template <class elemType>
class linkQueue
{
private:
	struct node
	{
		elemType data;
		node *next;
		node(const elemType &x, node *N=NULL)
		{
			data=x;
			next=N;
		}
		node():next(NULL){}
		~node() {}
	};
	node *front,*rear;
public:
	linkQueue() {front=rear=NULL;}
	~linkQueue(); 
	bool isEmpty() {return front==NULL;}
	void enQueue(const elemType &x);
	elemType deQueue();
	elemType getHead() {return front->data;}
};

template <class elemType>
void linkQueue<elemType>::enQueue(const elemType &x)
{
	if (rear==NULL)
		front=rear=new node(x);
	else
	{
		rear->next=new node(x);
		rear=rear->next;
	}
}

template <class elemType>
elemType linkQueue<elemType>::deQueue()
{
	node *tmp=front;
	elemType value=front->data;
	front=front->next;
	if (front==NULL) rear=NULL;
	delete tmp;
	return value;
}

template <class elemType>
linkQueue <elemType>::~linkQueue()
{
	node *tmp;
	while (front!=NULL)
	{
		tmp=front;
		front=front->next;
		delete tmp;
	}
}

//标准链表实现二叉树类
template <class Type>
class BinaryTree
{
private:
	struct Node
	{
		Node *left, *right;
		Type data;
		Node():left(NULL), right(NULL) {}
		Node(Type item, Node *L=NULL, Node *R=NULL)
		{
			data=item;
			left=L;
			right=R;
		}
		~Node() {}
	};
	Node *root;
public:
	BinaryTree():root(NULL) {}
	BinaryTree(const Type &value) { root=new Node(value);}
	~BinaryTree() { clear();}
	Type getRoot() const {return root->data;}
	Type getLeft() const {return root->left->data;}
	Type getRight() const {return root->right->data;}
	void makeTree(const Type &x, BinaryTree &lt, BinaryTree &rt)
	{
		root=new Node(x,lt.root,rt.root);
		lt.root=NULL;
		lr.root=NULL;
	}
	void delLeft()
	{
		BinaryTree tmp=root->left;
		root->left=NULL;
		tmp.clear();
	}
	void delRight()
	{
		BinaryTree tmp=root->right;
		root->right=NULL;
		tmp.clear();
	}
	bool isEmpty() const {return root==NULL;}
	void clear() 
	{
		if (root != NULL) clear(root);
		root=NULL;
	}
	int size() const {return size(root);}
	int height() const {return height(root);}
	void preOrder() const
	{
		if (root != NULL)
		{
			cout<<"\n前续遍历:";
			preOrder(root);
		}
	}
	void postOrder() const
	{
		if (root !=NULL)
		{
			cout<<"\n后续遍历";
			postOrder(root);
		}
	}
	void midOrder() const
	{
		if (root !=NULL)
		{
			cout<<"\n中序遍历";
			midOrder(root);
		}
	}
	void createTree(Type flag)
	{
		linkQueue<Node*> que;
		Node* tmp;
		Type x,ldata,rdata;
		cout<<"输入根结点:";
		cin>>x;
		root=new Node(x);
		que.enQueue(root);
		while (!que.isEmpty())
		{
			tmp=que.deQueue();
			cout<<"输入"<<tmp->data<<"的两个儿子（"<<flag<<"表示空结点）：";
			cin >> ldata >>rdata;
			if (ldata !=flag) que.enQueue(tmp->left=new Node(ldata));
			if (rdata !=flag) que.enQueue(tmp->right=new Node(rdata));
		}
		cout<<"create completed! \n";
	}
	//用于检查是否是完全二叉树的函数,根据结点标号来检查
	bool completecheck() 
	{
		if (getmax(root,1)==size()) return true;
		else return false;
	}
private:
	int height(Node *t) const
	{
		if (t==NULL) return 0;
		else
		{
			int lt=height(t->left),rt=height(t->right);
			return 1+((lt>rt? lt:rt));
		}
	}
	void clear(Node *t)
	{
		if (t->left != NULL) clear(t->left);
		if (t->right != NULL) clear(t->right);
		delete t;
	}
	int size(Node *t) const
	{
		if (t==NULL) return 0;
		return 1+size(t->left)+size(t->right);
	}
	void preOrder(Node *t) const
	{
		if (t != NULL)
		{
			cout << t->data << ' ';
			preOrder(t->left);
			preOrder(t->right);
		}
	}
	void postOrder(Node *t) const
	{
		if (t != NULL)
		{
			postOrder(t->left);
			postOrder(t->right);
			cout << t->data << ' ';
		}
	}
	void midOrder(Node *t) const
	{
		if (t != NULL)
		{
			midOrder(t->left);
			cout << t->data << ' ';
			midOrder(t->right);
		}
	}
	//利用完全二叉树的标号最小的性质来检查是否是完全二叉树
	int getmax(Node *t, int x)
	{
		int maxnum=x,tmp;
		if (t->left !=NULL) 
		{
			tmp=getmax(t->left,x*2);
			if (tmp>maxnum) maxnum=tmp;
		}//完全二叉树父亲节点的左子树标号是其标号的两倍
		if (t->right != NULL) 
		{
			tmp=getmax(t->right, x*2+1);
			if (tmp>maxnum) maxnum=tmp;
		}//完全二叉树父亲节点的右子树标号是其标号的两倍加上1
		return maxnum;
	}
};

//主程序
int main()
{
	BinaryTree<char> tree;
	tree.createTree('@');
	if (tree.completecheck())
		cout << "这是一棵完全二叉树";
	else cout << "这不是一棵完全二叉树";
	cout << endl;
	system("pause");
}