#include <iostream>
#include <fstream>
//#include <cmath>
using namespace std;

//����ǰһ��Ķ���,��Ϊdouble����
class IntQueue
{
public:
	IntQueue(int capacity=100)	//���캯��
	{
		data=new double[capacity];
		maxSize=capacity;
		currentSize=0;
	}
	IntQueue(const int data[], int size);//���ƹ���
	~IntQueue() {delete [] data; }
	bool isEmpty() const {return currentSize==0;}//�п�
	void enQueue(double x);
	double deQueue();
	double getHead() const {return data[1];}//�õ��׽ڵ�
	int findMin(double x);//ʵ����ĿҪ��
	void decreaseKey(int i, double value);//ʵ����ĿҪ��
	double getNumber(int a) const {return data[a];}
private:
	int currentSize;
	double *data;
	int maxSize;
	void doubleSpace();
	void buildHeap();
	void percolateDown(int hole);
};

//��������д��
void IntQueue::enQueue(double x)
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

double IntQueue::deQueue()
{
	double minItem=data[1];
	data[1]=data[currentSize--];
	percolateDown(1);
	return minItem;
}

void IntQueue::percolateDown(int hole)
{
	int child;
	double tmp=data[hole];
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
	double *tmp=data;
	maxSize*=2;
	data=new double[maxSize];
	for (int i=0; i<=currentSize; i++) data[i]=tmp[i];
	delete [] tmp;
}

//ȫ�����������Ҫ���ֵ�ı��
int IntQueue::findMin(double x)
{
	double num=-1;
	int ans=0;
	for (int i=1; i<=currentSize; i++)
	{
		if (data[i]>=x && (num==-1 || num>data[i]))
		{
			ans=i; num=data[i];
		}
	}
	return ans;
}

//�ı�ֵ֮���ٵ���λ��
void IntQueue::decreaseKey(int i, double value)
{
	double tmp;
	data[i]-=value;
	tmp=data[i];
	int hole=i;
	while (hole>1 && tmp<data[hole/2])
	{
		data[hole]=data[hole/2];
		hole=hole/2;
	}
	data[hole]=tmp;
}

//������
int main()
{
	ifstream fin;
	fin.open("in.txt");
	ofstream fout;
	fout.open("out.txt");
	double *a;
	IntQueue que1;
	IntQueue que2;   //�����ʣ���װ�������ֵ
	int i,n,tmp,result=1;
	double w;
	fin >> n;   //�ȴ�in.txt�ļ��ж�ȡ��������
	a=new double[n];
	que2.enQueue(1.0);	 //���ȼ���һ���ձ���
	for (i=1; i<=n; i++)
	{
	    fin >> w;
	    que1.enQueue(w);
	}  //�ٴ�in.txt�ļ��ж�ȡ��������ֵ���������ȼ�����que1
	for (i=1; i<=n; i++)
	{
	    a[i-1]=que1.deQueue();
	}  //������ֵ������a�д�С��������
	for (i=n; i>=1; i--)
	{
	    w=a[i-1];   //������a��Ԫ�ذ��±�Ӵ�С���
		tmp=que2.findMin(w);   //Ѱ�ҿ��Է��µ���������
		if (tmp==0)	 //�Ҳ������ú���ʱ�����
		{
			que2.enQueue(1-w);
			result++;  //��result��¼���ú��Ӹ���
		}
		else	//�ҵ����ú���ʱ�����
		{
			que2.decreaseKey(tmp,w);
		}
	}
	cout <<"���ٿ���" << result <<"�����ӽ������";
	fout << result;
	fin.close();
	fout.close();
}
