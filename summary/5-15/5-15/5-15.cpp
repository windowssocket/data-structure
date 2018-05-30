#include <iostream>
using namespace std;
//���������,���ڶ�����
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

//˳����ʵ�ֶ�����
template <class Type>
class BinaryTree
{
private:
	int maxsize;
	Type *data;
	bool *flag;

public:
	BinaryTree(const int &x=2000)
	{
		maxsize=x;
		data=new Type[maxsize];
		flag=new bool[maxsize];
		for (int i=0; i<=maxsize; i++) {flag[i]=false;}
	}
	~BinaryTree() {delete [] data;}
	Type getRoot() const {return data[1];}
	Type getLeft(const int &x) const {return data[2*x+1];}
	Type getRight(const int &x) const {return data[2*x];}
	//����,���ռ䲻��,ʹ�ÿռ䷭������
	void createTree(Type ff)
	{
		linkQueue<int> que;
		int tmp;
		Type x,ldata,rdata;
		cout << "��������:";
		cin >> x;
		data[1]=x;
		flag[1]=true;
		que.enQueue(1);
		while (!que.isEmpty())
		{
			tmp=que.deQueue();
			if (tmp*2>=maxsize) doublespace();
			cout << "����" << data[tmp] << "���������ӣ�" << ff << "��ʾ�ս�㣩��";
			cin >> ldata >>rdata;
			if (ldata != ff) 
			{
				data[tmp*2]=ldata;
				flag[tmp*2]=true;
				que.enQueue(tmp*2);
			}
			if (rdata != ff) 
			{
				data[tmp*2+1]=rdata;
				flag[tmp*2+1]=true;
				que.enQueue(tmp*2+1);
			}
		}
		cout << "create completed! \n";
	}
	void preOrder()								//ǰ�����
	{
		cout << "ǰ������Ľ��Ϊ��";
		preOrder(1);
		cout << endl;
	}
	void postOrder()							//�������
	{
		cout << "��������Ľ��Ϊ��";
		postOrder(1);
		cout << endl;
	}
	void midOrder()								//�������
	{
		cout << "��������Ľ��Ϊ: ";
		midOrder(1);
		cout << endl;
	}
	void preOrder(const int &x) const			//ǰ�����ʵ��
	{
		cout << data[x] << ' ';
		if (flag[2*x]) preOrder(2*x);
		if (flag[2*x+1]) preOrder(2*x+1);
	}
	void postOrder(const int &x) const			//�������ʵ��
	{
		if (flag[2*x]) postOrder(2*x);
		if (flag[2*x+1]) postOrder(2*x+1);
		cout << data[x] << ' ';
	}
	void midOrder(const int &x) const			//�������ʵ��
	{
		if (flag[2*x]) midOrder(2*x);
		cout << data[x] << ' ';
		if (flag[2*x+1]) midOrder(2*x+1);
	}
	int height() {return height(1); }			//��߶�
	int height(const int &x)					//�߶ȼ���
	{
		if (flag[x]==false) return 0;
		else
		{
			int lt=height(x*2);
			int rt=height(x*2+1);
			return 1+( lt>rt? lt:rt);
		}
	}
	void clear(const int &x)	
	{
		if (flag[x*2]==true) clear(x*2);
		if (flag[x*2+1]==true) clear(x*2+1);
		flag[x]=false;
	}
	int getsize() { return size(1); }			//���ģ
	int size(const int &x)						//���ģʵ��
	{
		if (flag[x]==false) return 0;
		return 1+size(x*2)+size(x*2+1);
	}
	bool isEmpty() const {return flag[1]==false;}
	void doublespace()							//�ռ䷭��
	{
		Type *tmp1=data;
		bool *tmp2=flag;
		data=new Type[maxsize*2];
		flag=new bool[maxsize*2];
		for (int i=1; i<=maxsize*2; i++) flag[i]=false;
		for (int i=1; i<=maxsize; i++)
		{
			data[i]=tmp1[i];
			flag[i]=tmp2[i];
		}
		maxsize*=2;
		delete tmp1;
		delete tmp2;
	}
};
//������
int main()
{
	BinaryTree<char> tree;
	tree.createTree('@');
	cout << "�߶�Ϊ��" << tree.height() << endl;
	cout << "��ģΪ��" << tree.getsize() << endl;
	tree.preOrder();
	tree.midOrder();	
	tree.postOrder();
	system("pause");
}