#include <iostream>
using namespace std;

//���������
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

//�����ֵ�����ʵ�ֵĶ�����
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
	//��������
	void createTree(Type flag)
	{
		linkQueue<Node*> que;
		Node* tmp;
		Type x,t;
		cout << "��������: ";
		cin >> x;
		root=new Node(x);
		que.enQueue(root);
		int n;
		while (!que.isEmpty())
		{
			tmp=que.deQueue();
			cout << "����" << tmp->data << "�Ķ��Ӹ���: ";	//ͳ�ƶ��ӵĸ���
			cin >> n;
			if (n==0) continue;
			cout << "����" << tmp->data << "�Ķ��ӣ�" << flag << "��ʾ�ս�㣩��";
			for (int i=1; i<=n; i++)
			{
				cin >> t;
				if (i==1)	//��һ��������Ϊ���ӽ��
				{
					que.enQueue(tmp->son=new Node(t));					
					tmp=tmp->son;
				}
				else		//��Ϊ��һ�����ӵ��ֵܽ��
				{
					que.enQueue(tmp->brother=new Node(t));
					tmp=tmp->brother;
				}
			}
		}
		cout << "create completed! \n";
	}
	bool isEmpty () const {return root==NULL;}
	void preOrder()			//ǰ������տ�
	{
		cout << "ǰ������Ľ��Ϊ��";
		preOrder(root);
		cout << endl;
	}
	void postOrder()		//��������տ�
	{
		cout << "��������Ľ��Ϊ��";
		postOrder(root);
		cout << endl;
	}
	void preOrder(Node *t)		//ǰ�����ʵ��
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
	void postOrder(Node *t)			//�������ʵ��
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
	void layerOrder()	//��α���ʵ��
	{
		cout << "��α����Ľ��Ϊ��";
		linkQueue<Node*> que;
		que.enQueue(root);
		while (!que.isEmpty())
		{
			Node* temp;
			temp=que.deQueue();
			if (temp != NULL)
			{
				cout << temp->data << ' ';
				Node* t=temp->son;	//��ͣ��
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

//������
int main()
{
	BrotherTree<char> tree;
	tree.createTree('@');
	tree.preOrder();
	tree.postOrder();
	tree.layerOrder();
	system("pause");
}
