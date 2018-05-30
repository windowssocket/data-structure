#ifndef _DISJOINTSET_H_
#define _DISJOINTSET_H_

#include<iostream>
using namespace std;

class DisjointSet{
public:
    int size;
    int *parent;


    DisjointSet(int n);
    ~DisjointSet(){delete[] parent;}
    void Union(int root1, int root2);
    int Find(int x);

};

DisjointSet::DisjointSet(int n)
{
    size=n;
    parent=new int[n];
    for(int i=0; i<n; ++i) parent[i]=-1;
}

void DisjointSet::Union(int root1, int root2)
{
    if(root1==root2) return;
    else if(parent[root1]<parent[root2]){
        parent[root1]+=parent[root2];
        parent[root2]=root1;
    }
    else{
        parent[root2]+=parent[root1];
        parent[root1]=root2;
    }
}

int DisjointSet::Find(int x)
{
    int *tmp=new int[size],n=0;  //tmp used as a stack to save the node passed
    while(parent[x]>=0){
        tmp[n++]=x;
        x=parent[x];
    }

    for(int i=0; i<n; ++i) parent[tmp[i]]=x;  //simplify the road
    delete[] tmp;

    return x;
}
#endif // _DISJOINTSET_H_
