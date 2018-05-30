#include"DoubleQueue.h"
#include<fstream>

int main()
{
	ifstream fin("in.txt");
	ofstream fout("out.txt");
	DoubleQueue box;
	int n,min;
	double x;
	
	fin>>n;
	for(int i=0; i<n; ++i) box.enQueue(1.00000001);  //use n boxes at most

	for(int i=0; i<n; ++i){
		fin>>x;
		box.decreaseKey(box.findMin(x),x);  //find the min value box to save x ,then the value of the box is decrease x
	}
	for(min=0; box.getHead()<1; ++min) box.deQueue(); //the box value less than 1 is used
	fout<<min<<endl;

	return 0;
}