#include <iostream>
using namespace std;

//������ĿҪ�����
class IntQueue
{
public:
	IntQueue(int capacity=100)//���캯��
	{
		data=new int[capacity];
		maxSize=capacity;
		currentSize=0;
	}
	IntQueue(const int data[], int size);//���ƹ���
	~IntQueue() {delete []data; }
	bool isEmpty() const {return currentSize==0;}//�п�
	void enQueue(int x);//���
	int deQueue();//����
	int getHead() const {return data[1];}//�õ��׽ڵ�
	int findMin(int x);//������ĿҪ��
	void decreaseKey(int i, int value);//������ĿҪ��
private:
	int currentSize;
	int *data;
	int maxSize;

	void doubleSpace();
	void buildHeap();
	void percolateDown(int hole);
};

//����ʵ��
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

int IntQueue::findMin(int x)//����ȫ���Ľ�����Ѱ��
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

void IntQueue::decreaseKey(int i, int value)//��ȥvalue,Ȼ��������ϵ�����ֱ���ﵽλ��
{
	int tmp;
	data[i]-=value;
	tmp=data[i];
	int hole=i;
	while (hole>1 && tmp<data[hole/2])//���ϵ���
	{
		data[hole]=data[hole/2];
		hole=hole/2;
	}
	data[hole]=tmp;
}

//���Գ���,�����鱾��ͼ6-20�������͵����ȼ�����
int main()
{
	IntQueue que;
	int n,tmp;
	cout << "������Ԫ�ظ���:";
	cin >> n;
	cout << "������Ԫ��ֵ:";
	for (int i=1; i<=n; i++)
	{
		cin >> tmp;
		que.enQueue(tmp);
	}//��������
	cout << "����findMin��ķ���ֵΪ��";
	cout << que.findMin(9) << endl;
	que.decreaseKey(4,7);
	cout << "��������decreaseKey��ı�5�����СԪ���±�ֵΪ��";
	cout << que.findMin(5) << endl;
}
