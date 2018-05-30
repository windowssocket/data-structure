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

class server
{	
private:
	int trucktime;
	int truck_wait;
	int bustime;
	int bus_wait;
	int trucknum;
	int busnum;

public:
	double Ave_time_bus;
	double Ave_time_truck;
	void getinf();
	void calc();
	void output();
};

void server::getinf()
{
	bus_wait=0;
	truck_wait=0;
	cout<<"每隔多少分钟来一辆客车? ";
	cin>>bustime;
	cout<<"总共来多少辆客车? ";
	cin>>busnum;
	cout<<"每隔多少分钟来一辆货车? ";
	cin>>trucktime;
	cout<<"总共来多少辆货车? ";
	cin>>trucknum;
}//获得相关信息

void server::calc()
{
	int ship_time=0;
	int onship_all;
	int onship_bus;
	int onship_truck;
	linkQueue<int> bus,truck;
	for (int i=0;i<busnum;i++)
		bus.enQueue(bustime*i+bustime);
	for (int i=0;i<trucknum;i++)
		truck.enQueue(trucktime*i+trucktime);
	while (!bus.isEmpty()||!truck.isEmpty())
	{
		ship_time+=10;
		onship_all=0;
		onship_bus=0;
		onship_truck=0;
		//while (onship_all < 10)
		//{
			bool flag=false;
			if (!bus.isEmpty())
				if (bus.getHead()<=ship_time) flag=true;
			if (!truck.isEmpty())
				if (truck.getHead()<=ship_time)
					flag=true;
			if (!flag) continue;
			while ((!bus.isEmpty())&&(onship_all<10))//让客车上船
			{
				if (bus.getHead()>ship_time) break;
				bus_wait+=ship_time-bus.deQueue();//等待时间等于开船时间减去进队时间
				onship_bus++;
				onship_all++;
				if ((onship_bus%4==0)&&(!truck.isEmpty()))//每四辆客车才能上一辆货车
					if (truck.getHead()<=ship_time)
					{
						truck_wait+=ship_time-truck.deQueue();//等待时间等于开船时间减去进队时间
						onship_truck++;
						onship_all++;
					}
			}
			while ((!truck.isEmpty()) && (onship_all<10))//如果客车没有了,上货车
			{
				if (truck.getHead()>ship_time) break;
				truck_wait+=ship_time-truck.deQueue();
				onship_truck++;
				onship_all++;
			}
		//}
	}
	Ave_time_bus=bus_wait;
	Ave_time_truck=truck_wait;
	Ave_time_bus /=busnum;//计算客车平均等待时间
	Ave_time_truck /=trucknum;//计算货车平均等待时间
}

void server::output()
{
	cout<<"每辆客车的平均等待时间为："<< Ave_time_bus<<"分钟"<<endl;
	cout<<"每辆货车的平均等待时间为："<< Ave_time_truck<<"分钟"<<endl;
}//输出两种车子的平均等待时间

int main()
{
	server s;
	s.getinf();
	s.calc();
	s.output();
	system("pause");
}