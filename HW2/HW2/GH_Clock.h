/*
 *File:GH_Clock.h
 *Version:1.0
 *-------------------------------------------
 *Usage:a data type of the time 
 *Remark:a primary class
 */

#ifndef _GH_Clock_h
#define _GH_Clock_h

#include<iostream>
using namespace std;

class Clock
{
  public:
	  Clock();       //constructor,default is zero
	  Clock(int);    //constructor,parameter is total second
	  Clock(int,int,int); //constructor,the parameter is hour,minute,second
	  
	  void SetClock(int,int,int); //set the number of clock
	  operator int();   //return totalSecond

	  friend Clock operator+(const Clock&, const Clock&); //friend func.+operator overloading
	  friend Clock operator-(const Clock&, const Clock&); //friend func.-operator overloading
	  
	  friend istream& operator>>(istream&, Clock&);       //friend func.>>operator overloading
	  friend ostream& operator<<(ostream&, const Clock&); //friend func.<<operator overloading

  private:
	  int totalSecond;  //the total second from 0:00:00 to this time 

};


#endif

