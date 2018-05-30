#include <iostream>
#include "DisjointSet.h"
using namespace std;

int main()
{
    int n,a,b;
    cout<<"n?";
    cin>>n;
    DisjointSet s(n);
    while(true){
        cout<<"connect a b";
        cin>>a>>b;
        if(a<0 || b<0) break;
        s.Union(s.Find(a),s.Find(b));
    }
	for(int i=0; i<n; ++i)s.Find(i);
	for(int i=0; i<n; ++i) cout<<i<<' '<<s.parent[i]<<endl;
    return 0;
}
