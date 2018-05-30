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
	cout<<"ÿ�����ٷ�����һ���ͳ�? ";
	cin>>bustime;
	cout<<"�ܹ����������ͳ�? ";
	cin>>busnum;
	cout<<"ÿ�����ٷ�����һ������? ";
	cin>>trucktime;
	cout<<"�ܹ�������������? ";
	cin>>trucknum;
}//��������Ϣ

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
			while ((!bus.isEmpty())&&(onship_all<10))//�ÿͳ��ϴ�
			{
				if (bus.getHead()>ship_time) break;
				bus_wait+=ship_time-bus.deQueue();//�ȴ�ʱ����ڿ���ʱ���ȥ����ʱ��
				onship_bus++;
				onship_all++;
				if ((onship_bus%4==0)&&(!truck.isEmpty()))//ÿ�����ͳ�������һ������
					if (truck.getHead()<=ship_time)
					{
						truck_wait+=ship_time-truck.deQueue();//�ȴ�ʱ����ڿ���ʱ���ȥ����ʱ��
						onship_truck++;
						onship_all++;
					}
			}
			while ((!truck.isEmpty()) && (onship_all<10))//����ͳ�û����,�ϻ���
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
	Ave_time_bus /=busnum;//����ͳ�ƽ���ȴ�ʱ��
	Ave_time_truck /=trucknum;//�������ƽ���ȴ�ʱ��
}

void server::output()
{
	cout<<"ÿ���ͳ���ƽ���ȴ�ʱ��Ϊ��"<< Ave_time_bus<<"����"<<endl;
	cout<<"ÿ��������ƽ���ȴ�ʱ��Ϊ��"<< Ave_time_truck<<"����"<<endl;
}//������ֳ��ӵ�ƽ���ȴ�ʱ��

int main()
{
	server s;
	s.getinf();
	s.calc();
	s.output();
	system("pause");
}