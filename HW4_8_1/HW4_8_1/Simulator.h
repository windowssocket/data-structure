#ifndef _simulator_h
#define _simulator_h

#include<iostream>
#include<queue>
#include"GH_Random.h"
using namespace std;

class Simulator
{
	private:
		double totalTime;

	public:
		Simulator(double time):totalTime(time){}
		double avgWaitTime(double interval, double p); //the bus:truck is 1:p
};

#endif