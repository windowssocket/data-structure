#include <iostream>
using namespace std;

//链表队列类
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

//儿子兄弟链表实现的二叉树
template <class Type>
class BrotherTree
{
private:
	struct Node
	{
		Node *son, *brother;
		Type data;
		Node():son(NULL),brother(NULL){}
		Node(Type item, Node *s=NULL, Node *b=NULL)
		{
			data=item;
			son=s;
			brother=b;
		}
		~Node() {}
	};
	Node *root;

public:
	BrotherTree():root(NULL) {}
	BrotherTree(const Type &value) { root=new Node(value);}
	~BrotherTree() {}
	//建树函数
	void createTree(Type flag)
	{
		linkQueue<Node*> que;
		Node* tmp;
		Type x,t;
		cout << "输入根结点: ";
		cin >> x;
		root=new Node(x);
		que.enQueue(root);
		int n;
		while (!que.isEmpty())
		{
			tmp=que.deQueue();
			cout << "输入" << tmp->data << "的儿子个数: ";	//统计儿子的个数
			cin >> n;
			if (n==0) continue;
			cout << "输入" << tmp->data << "的儿子（" << flag << "表示空结点）：";
			for (int i=1; i<=n; i++)
			{
				cin >> t;
				if (i==1)	//第一个儿子作为儿子结点
				{
					que.enQueue(tmp->son=new Node(t));					
					tmp=tmp->son;
				}
				else		//作为第一个儿子的兄弟结点
				{
					que.enQueue(tmp->brother=new Node(t));
					tmp=tmp->brother;
				}
			}
		}
		cout << "create completed! \n";
	}
	bool isEmpty () const {return root==NULL;}
	void preOrder()			//前序遍历空壳
	{
		cout << "前序遍历的结果为：";
		preOrder(root);
		cout << endl;
	}
	void postOrder()		//后序遍历空壳
	{
		cout << "后序遍历的结果为：";
		postOrder(root);
		cout << endl;
	}
	void preOrder(Node *t)		//前序遍历实现
	{
		cout << t->data << ' ';
		if (t->son != NULL)
		{
			preOrder(t->son);
			Node* tmp=t->son->brother;
			while (tmp != NULL)
			{
				preOrder(tmp);
				tmp=tmp->brother;
			}
		}
	}
	void postOrder(Node *t)			//后序遍历实现
	{
		if (t->son != NULL)
		{
			postOrder(t->son);
			Node* tmp=t->son->brother;
			while (tmp != NULL)
			{
				postOrder(tmp);
				tmp=tmp->brother;
			}
		}
		cout << t->data << ' ';
	}
	void layerOrder()	//层次遍历实现
	{
		cout << "层次遍历的结果为：";
		linkQueue<Node*> que;
		que.enQueue(root);
		while (!que.isEmpty())
		{
			Node* temp;
			temp=que.deQueue();
			if (temp != NULL)
			{
				cout << temp->data << ' ';
				Node* t=temp->son;	//不停的
				if (t != NULL)
				{
					que.enQueue(t);
					t=t->brother;
					while (t != NULL)
					{
						que.enQueue(t);
						t=t->brother;
					}
				}
			}
		}
		cout << endl;
	}
};

//主函数
int main()
{
	BrotherTree<char> tree;
	tree.createTree('@');
	tree.preOrder();
	tree.postOrder();
	tree.layerOrder();
	system("pause");
}
