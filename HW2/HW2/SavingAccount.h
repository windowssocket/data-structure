/*
 *File:SavingAccount.h
 *Version:1.0
 *-------------------------------------------
 *Usage:save the information of the depositor and caculator it
 *Remark:accomplish a program about ¡¯Bank Deposit¡¯
 */

#ifndef _SavingAccount_h
#define _SavingAccount_h

#include"GH_Clock.h"
#include<iostream>
using namespace std;


class SavingAccount
{
  public:
	  SavingAccount();  //constructor
	  SavingAccount(char*,int,Clock,Clock,int);  //constructor
	  ~SavingAccount();  //destructor

	  void SetSavingAccount(char*,int,Clock,Clock,int);  //edit the value
	  
	  static void ChangeInterestRates();  //change the interest rates

	  inline double InterestDue()const;  //calculate interest due, explicit inline function
	  inline double AmountDue()const;    //calculate amount due, explicit inline function

	  friend istream& operator>>(istream&, SavingAccount&);        //friend func. >>operator overloading
	  friend ostream& operator<<(ostream&, const SavingAccount&);  //friend func. <<operator overloading


  private:
	  char* customerID;  //the ID of the customer
	  int depositAmount; //the amount that the customer saving
	  Clock arrivedTime; //the time the customer arrived
	  Clock finishedTime;//the time the customer finished
	  int depositType;   //0:three months  1:half a year  2:one year  3:two years  4:three years  5:five years

	  SavingAccount(const SavingAccount&);	//freeze the copy constructor

	  static double interestRates[6];  //the interest rates of the index Deposit type

};


inline double SavingAccount::InterestDue()const
{
	double depositYear;

	switch(depositType)
	{
	  case 0: depositYear=0.25; break;
	  case 1: depositYear=0.5; break;
	  case 2: depositYear=1; break;
	  case 3: depositYear=2; break;
	  case 4: depositYear=3; break;
	  case 5: depositYear=5; break;
	  default: depositYear=0; break;
	}

	return depositAmount*depositYear*SavingAccount::interestRates[depositType]*0.8;
}


inline double SavingAccount::AmountDue()const
{
	return depositAmount+InterestDue();
}


#endif