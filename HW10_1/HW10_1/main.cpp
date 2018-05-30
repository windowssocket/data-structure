#include <iostream>
#include "Sort.h"
#include <fstream>
using namespace std;

int main()
{
    int k,a[20]={1,2,9,4,10,5,2,5,2,0,3,2,1,8,4,3,6,1,4,2};
    k=removeDiff(a,20);
	cout<<k<<endl;
    for(int i=0; i<k; ++i) cout<<a[i]<<' ';
    return 0;
}
