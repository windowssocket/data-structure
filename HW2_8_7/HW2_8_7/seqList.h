#ifndef _seqList_h
#define _seqList_h

#include<iostream>
using namespace std;

class OutOfBound{};
class IllegalSize{};

template<class elemType>
class seqList
{
	private:
		elemType *data;
		int currentLength;
		int maxSize;

		void doubleSpace();
	
	public:
		seqList(int initSize=10);
		//~seqList(){delete[] data;}
		void clear(){currentLength=0;}
		void length()const{return currentLength;}
		void insert(int i, const elemType &x);
		elemType visit(int i) const;
		void traverse() const;

		//the function below is added
		void input(elemType endElem);  //this function is help to test the class
		seqList operator=(const seqList &R); 
		friend seqList operator+<>(const seqList &s1, const seqList &s2);
};

#endif

