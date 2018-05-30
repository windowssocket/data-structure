#include"Shape.h"
#include"InvTriangle.h"
#include"UpTriangle.h"
#include"Diamond.h"
#include"Rectangle.h"
#include"Square.h"
#include"Polygon.h"
#include<iostream>
using namespace std;

int main(void)
{
	Shape *sp;

	UpTriangle upt;   //upright isosceles triangle
	InvTriangle inv;  //inverted isosceles triangle
	Rectangle rec;    //rectangle
	Square squ;       //square
	Diamond dia;      //diamond
	Polygon pol;      //polygon

	cout<<"Input 1 to choose upright isosceles triangle;"<<endl
	<<"Input 2 to choose inverted isosceles triangle;"<<endl
	<<"Input 3 to choose rectangle;"<<endl
	<<"Input 4 to choose square;"<<endl
	<<"Input 5 to choose diamond;"<<endl
	<<"Input 6 to choose polygon."<<endl
	<<"Default input to exit."<<endl<<endl;

	while(true)
	{
		int mode;

		cout<<"Your choice:";
		cin>>mode;
		cout<<endl;

		switch(mode)
		{
		 case 1: sp=&upt; break;
		 case 2: sp=&inv; break;
		 case 3: sp=&rec; break;
		 case 4: sp=&squ; break;
		 case 5: sp=&dia; break;
		 case 6: sp=&pol; break;
		 default: cout<<"Thank you for using the class!"<<endl; return 0;  //exit the program
		}

		sp->Input();cout<<endl;
		sp->Print();
		cout<<"________________________________________________________"<<endl<<endl;
	}

	return 0;
}

