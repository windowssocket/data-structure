#include"SavingAccount.h"
#include"GH_Queue.h"
#include"GH_Clock.h"
#include"GH_Random.h"
#include<iostream>
using namespace std;


Clock Max(Clock c1, Clock c2)
{
	if(int(c1)>int(c2)) return c1;
	else return c2;
}


void main()
{
	SavingAccount customer[20];
	Queue arrLine(20);   //the queue of the time the customer arrived;

	for(int i=0; i<20; ++i)
	{
		static Clock time(8,0,0);   //the beginning time 8:00:00

		time=time+(Clock)Random(180,480);  //generate random time they arrived
		arrLine.Enqueue(time);  //save the time they arrived;
	}

	for(int i=0; i<20; ++i)
	{
		static int DepositAmount,DepositType;
		static char *tmpID;   //temporary store customerID
		static Clock spendTime,finTime(8,0,0),arrTime;

		tmpID=RandomLine(10,'0','9');      //generate random customer ID
		DepositAmount=Random(1000,50000);  //generate random amout they deposited
		DepositType=Random(0,5);           //generate random type they deposited

		arrTime=arrLine.Dequeue();
		spendTime=(Clock)Random(120,420);   //generate random time the staff spend

		finTime=Max(arrTime,finTime)+spendTime;

		customer[i].SetSavingAccount(tmpID,DepositAmount,arrTime,finTime,DepositType);
		
		delete[] tmpID;
	}

	for(int i=0; i<10; ++i) cout<<customer[i];

	customer->ChangeInterestRates();   //change the interest rates

	cout<<endl<<endl;
	cout<<"After the interest rates changed"<<endl;
	cout<<"------------------------------------------------------------------------------"<<endl;
	for(int i=10; i<20; ++i) cout<<customer[i];


}