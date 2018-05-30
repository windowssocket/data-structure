#include"Shape.h"
#include"InvTriangle.h"
#include"UpTriangle.h"
#include"Diamond.h"
#include"Rectangle.h"
#include"Square.h"
#include"Polygon.h"
#include"GH_Queue.h"
#include"GH_Queue.cpp"
#include"GH_Random.h"
#include<iostream>
using namespace std;

int main(void)
{
	Shape *sp; //the basic point
	Queue<Shape*> S;  //save the shape
	int mode=-1;  //the choice of the user

	cout<<"Input 1 to choose upright isosceles triangle;"<<endl
	<<"Input 2 to choose inverted isosceles triangle;"<<endl
	<<"Input 3 to choose rectangle;"<<endl
	<<"Input 4 to choose square;"<<endl
	<<"Input 5 to choose diamond;"<<endl
	<<"Input 6 to choose polygon."<<endl
	<<"Input 0 to to exit."<<endl<<endl;

	while(mode!=0)
	{
		cout<<"Your choice(0~6):";
		cin>>mode;
		cout<<endl;

		switch(mode)
		{
		 case 1: sp=new UpTriangle; break;
		 case 2: sp=new InvTriangle; break;
		 case 3: sp=new Rectangle; break;
		 case 4: sp=new Square; break;
		 case 5: sp=new Diamond; break;
		 case 6: sp=new Polygon; break;
		 
		 case 0: cout<<"_____________________________________________________________________________"<<endl
					 <<"_____________________________________________________________________________"<<endl
					 <<"You have finished the program"<<endl
					 <<"There are the graphs you have printed:"<<endl<<endl;
			     break;
		 
		 default: cout<<"Wrong input!"<<endl;
			      mode=-1;
		}

		if(mode>0)
		{
			sp->Input();cout<<endl;
			sp->Print();
			cout<<"________________________________________________________"<<endl<<endl;
			S.Enqueue(sp);  //save the point
		}
	}

	RandomInit(GetRandSeed());  //let the rand seed to the begin

	while(!S.IsEmpty())
	{
		sp=S.Dequeue();
		sp->Print();
		cout<<"________________________________________________________"<<endl<<endl;
	}

	cout<<"Thank you for using the class!"<<endl;

	return 0;
}

