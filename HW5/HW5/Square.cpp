#include"Square.h"

Square::Square():Rectangle(){}

Square::Square(int w, int l):Rectangle(w,w,l){}


void Square::Input()
{
	cout<<"Please input width:";

	while(true)  //input width and check it
	{
		cin>>width;

		if(width<=0)
		{
			cout<<endl<<"************ warning! **************"<<endl
				<<"width must be a positive integer!"<<endl
				<<"************************************"<<endl<<endl
				<<"Please input width again:";
			continue;
		}

		if(width>25)
		{
			cout<<endl<<"************ warning! **************"<<endl
				<<"This width is too large!"<<endl
				<<"width must be less than or equal to 25!"<<endl
				<<"************************************"<<endl<<endl
				<<"Please input width again:";
			continue;
		}

		break;
	}

	height=width;   //square is a rectangle where height equal to width

	cout<<"Please input location:";

	while(true)  //input location and check it
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

		if(location>=80-width)
		{
			cout<<endl<<"************ warning! **************"<<endl
				<<"This location is too large!"<<endl
				<<"location must be less than "<<80-width<<'!'<<endl
				<<"************************************"<<endl<<endl
				<<"Please input location again:";
			continue;
		}

		break;
	}
}
