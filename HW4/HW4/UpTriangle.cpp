#include"UpTriangle.h"
#include"GH_Random.h"

UpTriangle::UpTriangle():height(0),location(0){}

UpTriangle::UpTriangle(int h, int l):height(h),location(l){}

void UpTriangle::Input()
{
	cout<<"Please input height:";

	while(true)  //input height and check it
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

		if(location>80-2*height)
		{
			cout<<endl<<"************ warning! **************"<<endl
				<<"This location is too large!"<<endl
				<<"location must be less than or equal to "<<80-2*height<<'!'<<endl
				<<"************************************"<<endl<<endl
				<<"Please input location again:";
			continue;
		}

		break;
	}
}


void UpTriangle::Print() const
{
	for(int i=0; i<height; ++i)
	{
		for(int j=0; j<location+height-i-1; ++j)  cout<<' ';  //print space in each line

		for(int j=0; j<2*i+1; ++j) cout<<RandomChoose(2,'#','*');  //print shape in each line

		cout<<endl;
	}
}

	
