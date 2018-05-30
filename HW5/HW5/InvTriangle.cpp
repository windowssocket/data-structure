#include"InvTriangle.h"
#include"GH_Random.h"

InvTriangle::InvTriangle():UpTriangle(){}

InvTriangle::InvTriangle(int h, int l):UpTriangle(h,l){}


void InvTriangle::Print() const
{
	for(int i=0; i<height; ++i)
	{
		for(int j=0; j<location+i; ++j)  cout<<' ';  //print space in each line

		for(int j=0; j<2*(height-i)-1; ++j) cout<<RandomChoose(2,'#','*');  //print shape in each line

		cout<<endl;
	}
}