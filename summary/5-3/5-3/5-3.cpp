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
	node *front, *rear;

public:
	linkQueue() {front=rear=NULL;}
	~linkQueue(); 
	bool isEmpty() {return front==NULL;}
	void enQueue(const elemType &x);
	elemType deQueue();
	elemType getHead() {return front->data;}
};

//相应的函数实现
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
	if (front == NULL) rear=NULL;
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

//二叉树类
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
	Node* root;
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
	void createTree(Type flag)
	{
		linkQueue<Node*> que;
		Node* tmp;
		Type x,ldata,rdata;
		cout << "输入根结点:";
		cin>>x;
		root=new Node(x);
		que.enQueue(root);
		while (!que.isEmpty())
		{
			tmp=que.deQueue();
			cout<<"输入"<< tmp->data<<"的两个儿子（"<<flag<<"表示空结点）:";
			cin>>ldata>>rdata;
			if (ldata !=flag) que.enQueue(tmp->left=new Node(ldata));
			if (rdata !=flag) que.enQueue(tmp->right=new Node(rdata));
		}
		cout << "create completed! \n";
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
	bool isEmpty () const {return root==NULL;}
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
		if (root != NULL)
		{
			cout<<"\n后续遍历";
			postOrder(root);
		}
	}
	void midOrder() const
	{
		if (root != NULL)
		{
			cout<<"\n中序遍历";
			midOrder(root);
		}
	}
	//层次遍历函数  利用队列实现BFS
	void layerOrder() const
	{
		cout << "层次遍历结果为： ";
		linkQueue<Node*> que;
		que.enQueue(root);
		while (!que.isEmpty())
		{
			Node *temp;
			temp=que.deQueue();
			if (temp != NULL)  //按照每一层依次按先左后右的顺序排入队列
			{
				cout<<temp->data<<" ";
				que.enQueue(temp->left);
				que.enQueue(temp->right);
			}
		}
		cout<<endl;
	}
private:
	//封装起来的各种函数的实现
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
};

//简短测试函数
int main()
{
	BinaryTree<char> tree;
	tree.createTree('@');//用符号@表示空并构建二叉树
	tree.layerOrder();
	system("pause");
}