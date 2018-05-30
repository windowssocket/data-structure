#include"GH_Clock.h"


static int DayClock(int second)  //return the time that second represented
{
	if(second<0) return second%86400+86400;  //a day is 24:00:00 is 86400seconds
	else return second%86400;
}


Clock::Clock():totalSecond(0){}


Clock::Clock(int second):totalSecond(DayClock(second)){}


Clock::Clock(int hour,int minute,int second):totalSecond(DayClock(3600*hour+60*minute+second)){}


void Clock::SetClock(int hour, int minute, int second)
{
	Clock tmp(hour,minute,second);  //invoke constructor
	*this=tmp;
}


Clock::operator int()
{
	return totalSecond;
}


Clock operator+(const Clock &c1, const Clock &c2)
{
	return(DayClock(c1.totalSecond+c2.totalSecond));
}


Clock operator-(const Clock &c1, const Clock &c2)
{
	return(DayClock(c1.totalSecond-c2.totalSecond));
}


istream& operator>>(istream &is, Clock &c)
{
	int hour,minute,second;

	is>>hour>>minute>>second;
	c.SetClock(hour,minute,second);
	return is;
}


ostream& operator<<(ostream &os, const Clock &c)
{
	int hour,minute,second;

	hour=c.totalSecond/3600;
	minute=c.totalSecond%3600/60;
	second=c.totalSecond%3600%60;
	
	os<<hour/10<<hour%10<<':'<<minute/10<<minute%10
		<<':'<<second/10<<second%10;        //cout as "**:**:**"
	return os;
}
