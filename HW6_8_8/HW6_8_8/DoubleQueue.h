#ifndef _DoubleQueue_h
#define _DoubleQueue_h

#include<iostream>
using namespace std;

class DoubleQueue{
private:
	int currentSize;
	double *elem;
	int maxSize;

	void doubleSpace();
	void percolateDown(int hole);

public:
	DoubleQueue():currentSize(0),maxSize(2){elem=new double[2];}
	~DoubleQueue(){delete[] elem;}

	bool isEmpty() const {return currentSize==0;}
	void CreateTree();
	void enQueue(double x);
	double deQueue();
	double getHead() const{ return elem[1];}
	
	int findMin(double x);  //fin the min elem larger than x, return the index
	void decreaseKey(int i, double value);  //decrease the value of ith elem
};

#endif