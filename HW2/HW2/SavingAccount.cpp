#include"SavingAccount.h"
#include<iomanip>

static const double rate1[6]={0.0171,0.0207,0.0225,0.0270,0.0324,0.0360};
static const double rate2[6]={0.0180,0.0225,0.0252,0.0306,0.0369,0.0414};


double SavingAccount::interestRates[6]={rate1[0],rate1[1],rate1[2],rate1[3],rate1[4],rate1[5]}; 
//initialize the static value


SavingAccount::SavingAccount()
{
	customerID=new char[1];

}


SavingAccount::SavingAccount(char *ID, int amount, Clock arrTime, Clock finTime, int type)
{
	int length;
	for(length=0; ID[length]; ++length);  //get the length of customer ID
	customerID=new char[length+1];   //assigned addresses for the pointer

	for(int i=0; i<length; ++i) customerID[i]=ID[i];
	customerID[length]='\0';   //character'\0' using as the end of the string

	depositAmount=amount;
	arrivedTime=arrTime;
	finishedTime=finTime;
	depositType=type;
}


SavingAccount::~SavingAccount()
{
	delete[] customerID;
}


void SavingAccount::SetSavingAccount(char *ID, int amount, Clock arrTime, Clock finTime, int type)
{
	int length;
	for(length=0; ID[length]; ++length);  //get the length of customer ID
	customerID=new char[length+1];   //assigned addresses for the pointer

	for(int i=0; i<=length; ++i) customerID[i]=ID[i];

	depositAmount=amount;
	arrivedTime=arrTime;
	finishedTime=finTime;
	depositType=type;
}


void SavingAccount::ChangeInterestRates()
{
	for(int i=0; i<6; ++i)
	{
		SavingAccount::interestRates[i]=rate2[i];  //change the rate and default is 0
	}
}


istream& operator>>(istream &is, SavingAccount &info)
{
	char *tmp=new char[30];  //pre-allocation 30 addresses to store info.customerID
	int length;    //length of customerID
	
	is.getline(tmp,30,' ');  //get the customer ID
	
	for(length=0; tmp[length]; ++length);  //get the length of customerID
	
	delete[] info.customerID;
	info.customerID=new char[length+1];
	
	for(int i=0; i<=length; ++i) info.customerID[i]=tmp[i];  //copy from tmp to customerID
	
	delete[] tmp;

	is>>info.depositAmount>>info.arrivedTime>>info.finishedTime>>info.depositType;
	return is;
}


ostream& operator<<(ostream &os, const SavingAccount &info)
{
	os<<left;
	os<<"CustomerID:  "<<setw(14)<<info.customerID
		<<"ArrivedTime:   "<<info.arrivedTime<<"     "
		<<"FinishedTime: "<<info.finishedTime
		<<endl;
	os<<"DepositType:";
	
	switch(info.depositType)
	{
	  case 0: os<<" Three months  "; break;
	  case 1: os<<" Half a year   "; break;
	  case 2: os<<" One year      "; break;
	  case 3: os<<" Two years     "; break;
	  case 4: os<<" Three years   "; break;
	  case 5: os<<" Five years    "; break;
	  default: os<<" Others       ";
	}

	os<<left<<fixed;  //align left and show point
	os<<"DepositAmount: гд"<<setw(11)<<setprecision(2)<<double(info.depositAmount);
	
	os<<right;  //align right
	os<<"InterestRates:"<<setprecision(2)<<setw(7)
		<<100*SavingAccount::interestRates[info.depositType]<<'%'<<endl;

	os<<left; //align left
	os<<"InterestDue: гд"<<setw(12)<<setprecision(2)<<info.InterestDue()
		<<"AmountDue:     гд"<<setprecision(2)<<info.AmountDue()<<endl;
	os<<"------------------------------------------------------------------------------"<<endl;

	return os;

}

