#include <iostream>
using namespace std;

//按照题目要求进行
class IntQueue
{
public:
	IntQueue(int capacity=100)//构造函数
	{
		data=new int[capacity];
		maxSize=capacity;
		currentSize=0;
	}
	IntQueue(const int data[], int size);//复制构造
	~IntQueue() {delete []data; }
	bool isEmpty() const {return currentSize==0;}//判空
	void enQueue(int x);//入队
	int deQueue();//出队
	int getHead() const {return data[1];}//得到首节点
	int findMin(int x);//按照题目要求
	void decreaseKey(int i, int value);//按照题目要求
private:
	int currentSize;
	int *data;
	int maxSize;

	void doubleSpace();
	void buildHeap();
	void percolateDown(int hole);
};

//函数实现
void IntQueue::enQueue(int x)
{
	if (currentSize==maxSize-1) doubleSpace();
	int hole=++currentSize;
	while (hole>1 && x<data[hole/2])
	{
		data[hole]=data[hole/2];
		hole=hole/2;
	}
	data[hole]=x;
}

int IntQueue::deQueue()
{
	int minItem=data[1];
	data[1]=data[currentSize--];
	percolateDown(1);
	return minItem;
}

void IntQueue::percolateDown(int hole)
{
	int child;
	int tmp=data[hole];
	while (hole*2<=currentSize)
	{
		child=hole*2;
		if (child!=currentSize && data[child+1]<data[child]) child++;
		if (data[child]<tmp) data[hole]=data[child];
		    else break;
		hole=child;
	}
	data[hole]=tmp;
}

void IntQueue::buildHeap()
{
	for (int i=currentSize/2; i>0; i--)
		percolateDown(i);
}

void IntQueue::doubleSpace()
{
	int *tmp=data;
	maxSize*=2;
	data=new int[maxSize];
	for (int i=0; i<=currentSize; i++) data[i]=tmp[i];
	delete []tmp;
}

int IntQueue::findMin(int x)//遍历全部的结点进行寻找
{
	int ans=0,num=x-1;
	for (int i=1; i<=currentSize; i++)
	{
		if (data[i]>x && (num==x-1 || num>data[i]))
		{
			ans=i; num=data[i];
		}
	}
	return ans;
}

void IntQueue::decreaseKey(int i, int value)//减去value,然后进行向上调整，直到达到位置
{
	int tmp;
	data[i]-=value;
	tmp=data[i];
	int hole=i;
	while (hole>1 && tmp<data[hole/2])//向上调整
	{
		data[hole]=data[hole/2];
		hole=hole/2;
	}
	data[hole]=tmp;
}

//测试程序,按照书本上图6-20打入整型的优先级队列
int main()
{
	IntQueue que;
	int n,tmp;
	cout << "请输入元素个数:";
	cin >> n;
	cout << "请输入元素值:";
	for (int i=1; i<=n; i++)
	{
		cin >> tmp;
		que.enQueue(tmp);
	}//存入数据
	cout << "函数findMin后的返回值为：";
	cout << que.findMin(9) << endl;
	que.decreaseKey(4,7);
	cout << "经过函数decreaseKey后的比5大的最小元素下标值为：";
	cout << que.findMin(5) << endl;
}
