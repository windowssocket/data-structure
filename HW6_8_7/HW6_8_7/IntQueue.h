#ifndef _IntQueue_h
#define _IntQueue_h

#include<iostream>
using namespace std;

class IntQueue{
private:
	int currentSize;
	int *elem;
	int maxSize;

	void doubleSpace();
	void percolateDown(int hole);

public:
	IntQueue():currentSize(0),maxSize(2){elem=new int[2];}
	~IntQueue(){delete[] elem;}

	bool isEmpty() const {return currentSize==0;}
	void CreateTree();
	void enQueue(int x);
	void deQueue();
	int getHead() const{ return elem[1];}
	
	int findMin(int x);  //fin the min elem larger than x, return the index
	void decreaseKey(int i, int value);  //decrease the value of ith elem
};

#endif