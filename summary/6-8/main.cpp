#include <iostream>
#include <fstream>
//#include <cmath>
using namespace std;

//利用前一题的队列,改为double类型
class IntQueue
{
public:
	IntQueue(int capacity=100)	//构造函数
	{
		data=new double[capacity];
		maxSize=capacity;
		currentSize=0;
	}
	IntQueue(const int data[], int size);//复制构造
	~IntQueue() {delete [] data; }
	bool isEmpty() const {return currentSize==0;}//判空
	void enQueue(double x);
	double deQueue();
	double getHead() const {return data[1];}//得到首节点
	int findMin(double x);//实现题目要求
	void decreaseKey(int i, double value);//实现题目要求
	double getNumber(int a) const {return data[a];}
private:
	int currentSize;
	double *data;
	int maxSize;
	void doubleSpace();
	void buildHeap();
	void percolateDown(int hole);
};

//按照书上写的
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

//全部遍历求符合要求的值的标号
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

//改变值之后再调整位置
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

//主程序
int main()
{
	ifstream fin;
	fin.open("in.txt");
	ofstream fout;
	fout.open("out.txt");
	double *a;
	IntQueue que1;
	IntQueue que2;   //存的是剩余可装入的重量值
	int i,n,tmp,result=1;
	double w;
	fin >> n;   //先从in.txt文件中读取背包个数
	a=new double[n];
	que2.enQueue(1.0);	 //事先加入一个空背包
	for (i=1; i<=n; i++)
	{
	    fin >> w;
	    que1.enQueue(w);
	}  //再从in.txt文件中读取各个重量值，进入优先级队列que1
	for (i=1; i<=n; i++)
	{
	    a[i-1]=que1.deQueue();
	}  //让重量值在数组a中从小到大排列
	for (i=n; i>=1; i--)
	{
	    w=a[i-1];   //让数组a中元素按下标从大到小输出
		tmp=que2.findMin(w);   //寻找可以放下的最满背包
		if (tmp==0)	 //找不到可用盒子时的情况
		{
			que2.enQueue(1-w);
			result++;  //用result记录所用盒子个数
		}
		else	//找到可用盒子时的情况
		{
			que2.decreaseKey(tmp,w);
		}
	}
	cout <<"最少可用" << result <<"个盒子解决问题";
	fout << result;
	fin.close();
	fout.close();
}
