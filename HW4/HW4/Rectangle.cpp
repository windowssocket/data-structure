#include"Rectangle.h"
#include"GH_Random.h"

Rectangle::Rectangle():height(0),width(0),location(0){}

Rectangle::Rectangle(int h, int w, int l):height(h),width(w),location(l){}


void Rectangle::Input()
{
	cout<<"Please input height:";

	while(true)   //input height and check it
	{
		cin>>height;

		if(height<=0)
		{
			cout<<endl<<"************ warning! **************"<<endl
				<<"height must be a positive integer!"<<endl
				<<"************************************"<<endl<<endl
				<<"Please input height again:";
			continue;
		}

		if(height>25)
		{
			cout<<endl<<"************ warning! **************"<<endl
				<<"This height is too large!"<<endl
				<<"height must be less than or equal to 25!"<<endl
				<<"************************************"<<endl<<endl
				<<"Please input height again:";
			continue;
		}

		break;
	}

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

		if(width>=80)
		{
			cout<<endl<<"************ warning! **************"<<endl
				<<"This width is too large!"<<endl
				<<"width must be less than 80!"<<endl
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


void Rectangle::Print() const
{
	for(int i=0; i<height; ++i)
	{
		for(int j=0; j<location; ++j)  cout<<' ';  //print space in each line

		for(int j=0; j<width; ++j) cout<<RandomChoose(2,'#','*');  //print shape in each line

		cout<<endl;
	}
}