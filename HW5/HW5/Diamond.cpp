#include"Diamond.h"
#include"GH_Random.h"

Diamond::Diamond():diagonal(0),location(0){}

Diamond::Diamond(int d, int l):diagonal(d),location(l){}


void Diamond::Input()
{
	cout<<"Please input diagonal (must be odd number):";

	while(true)  //input diagonal and check it
	{
		cin>>diagonal;

		if(diagonal<=0)
		{
			cout<<endl<<"************ warning! **************"<<endl
				<<"diagonal must be a positive integer!"<<endl
				<<"************************************"<<endl<<endl
				<<"Please input diagonal again:";
			continue;
		}

		if(diagonal%2==0)
		{
			cout<<endl<<"************ warning! **************"<<endl
				<<"diagonal must be a odd number!"<<endl
				<<"************************************"<<endl<<endl
				<<"Please input diagonal again:";
			continue;
		}

		if(diagonal>25)
		{
			cout<<endl<<"************ warning! **************"<<endl
				<<"This diagonal is too large!"<<endl
				<<"diagonal must be less than or equal to 25!"<<endl
				<<"************************************"<<endl<<endl
				<<"Please input diagonal again:";
			continue;
		}

		break;
	}

	cout<<"Please input location:";

	while(true)   //input location and check it
	{
		cin>>location;

		if(location<0)
		{
			cout<<endl<<"************ warning! **************"<<endl
				<<"location can not be a negative integer!"<<endl
				<<"************************************"<<endl<<endl
				<<"Please input location again:";
			continue;
		}

		if(location>=80-diagonal)
		{
			cout<<endl<<"************ warning! **************"<<endl
				<<"This location is too large!"<<endl
				<<"location must be less than "<<80-diagonal<<'!'<<endl
				<<"************************************"<<endl<<endl
				<<"Please input location again:";
			continue;
		}

		break;
	}
}


void Diamond::Print()const
{
	UpTriangle aboveShape(diagonal/2+1,location);  
	InvTriangle belowShape(diagonal/2,location+1);
			//diamond is comibined by UpTriangle and InvTriangle
	aboveShape.Print();
	belowShape.Print();
}

