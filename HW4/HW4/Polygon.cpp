#include"Polygon.h"

Polygon::Polygon():width(0),location(0){}

Polygon::Polygon(int w, int l):width(w),location(l){}


void Polygon::Input()
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

		if(width>=10)
		{
			cout<<endl<<"************ warning! **************"<<endl
				<<"This width is too large!"<<endl
				<<"width must be less than 10!"<<endl
				<<"************************************"<<endl<<endl
				<<"Please input width again:";
			continue;
		}

		break;
	}

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

		if(location>80-2*width)
		{
			cout<<endl<<"************ warning! **************"<<endl
				<<"This location is too large!"<<endl
				<<"location must be less than or equal to "<<80-2*width<<'!'<<endl
				<<"************************************"<<endl<<endl
				<<"Please input location again:";
			continue;
		}

		break;
	}
}


void Polygon::Print()const
{
	UpTriangle aboveShape(width,location);  
	Rectangle  belowShape(2*width-2,2*width-1,location);
			//polygon is comibined by UpTriangle and Rectangle
	aboveShape.Print();
	belowShape.Print();
}