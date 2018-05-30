#ifndef _num_h
#define _num_h

#include<iostream>
#include<stack>
using namespace std;

struct node
{
	int data;
	node *next;

	node(int x):data(x),next(NULL){}
};

class Num
{
	friend istream& operator>>(istream &is, Num &num);
	friend ostream& operator<<(ostream &os, const Num &num);
	friend Num operator+(const Num& n1, const Num& n2);

	friend node* Plus(node *p1, node *p2);
	friend node* Minus(node *p1, node *p2);
	friend bool Bigger(node *p1, node *p2); //return true if |p1|>|p2|

	private:
		node *head;  //save data
		bool sign;

	public:
		Num(){head=new node(0);}
		~Num();
		Num& operator=(const Num &R);

};

#endif