#include"Simulator.h"
#include"GH_Random.h"

double Simulator::avgWaitTime(double interval,double p)
{
	queue<double> Q1,Q2;  //Q1 for bus while Q2 for truck
	int n=0;  //the total cars arrived
	double currentTime=0,runTime=10,waitTime=0; //runtime: the time of the ship arriving

	int arrBus=0,arrTruck=0,bus=0,truck=0; //collect the number os bus and truck
	while(runTime<=totalTime)
	{
		currentTime+=Random(0.0,interval);

		if(currentTime > runTime) //the ship has arrived
		{
			int arrivedCar=0, loop=4;  //loop is used as a counter
			
			while((!Q1.empty() || !Q2.empty()) && arrivedCar<10)
			{
				if( !Q1.empty() && loop!=0 || Q2.empty())
				{
					--loop;
					waitTime+=runTime-Q1.front();
					Q1.pop();
					++arrBus;
				}
				else
				{
					loop=4;
					waitTime+=runTime-Q2.front();
					Q2.pop();
					++arrTruck;
				}
				++arrivedCar;
			}

			while(runTime<currentTime) runTime+=10;
		}

		if(Random(0.0,1.0)>1.0/(1+p)){ Q1.push(currentTime); ++bus;}
		else{ Q2.push(currentTime); ++truck;}
		++n;

	}

	cout<<"总共到达客车"<<bus<<"辆，"<<"货车"<<truck<<"辆，共计"<<n<<"辆"<<endl
		<<"其中客车过江"<<arrBus<<"辆，"<<"货车过江"<<arrTruck<<"辆，"<<"共计"<<arrBus+arrTruck<<"辆"<<endl
		<<"平均等待时间(仅统计过江车辆)为"<<waitTime/(arrBus+arrTruck)<<endl;

	return waitTime/(arrBus+arrTruck);
}
