#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    ifstream fin;
    ofstream fout;
    fin.open("in.txt");
    fout.open("out.txt");
    char a[10],b[10];
    int c[10],d[10];
    int x=1,y=1,m=0,n=0,i,q,w;
    fin>>a;
    while(1)
    {
        if(!(a[m]>='A'&&a[m]<='Z')) break;
        ++m;
    }
    fin>>b;
    while(1)
    {
        if(!(b[n]>='A'&&b[n]<='Z')) break;
        ++n;
    }
    for(i=0;i<m;++i)
    {
        c[i]=a[i]-'A'+1;
    }
    for(i=0;i<n;++i)
    {
        d[i]=b[i]-'A'+1;
    }
    for(i=0;i<m;++i)
    {
        x=x*c[i];
    }
    for(i=0;i<n;++i)
    {
        y=y*d[i];
    }
    q=x%47;
    w=y%47;
    if(q==w) fout<<"GO"<<endl;
    else fout<<"STAY"<<endl;
    fin.close();
    fout.close();
    return 0;
}
