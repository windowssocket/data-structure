#ifndef _Set_h_
#define _Set_h_

#include<iostream>
using namespace std;

template<class Type>
class Set{
private:
	Type *elem;  //using array to save the elem
	int length;  //the num of the elem in set
	int maxSize; //the max length of the array

public:
	Set():length(0),maxSize(1){elem=new Type[1];}
	Set(Type x):length(1),maxSize(1){elem=new Type(x);}
	Set(const Set<Type> &S);
	~Set(){delete[] elem;}
	
	int Size(){return length;}
	void Input();                //input the set
	void Output()const;          //traverse the set
	Set operator+(const Set<Type> &s)const;  //union of sets
	Set operator*(const Set<Type> &s)const;  //intersection of sets  
	Set operator-(const Set<Type> &s)const;  //difference of sets 

	Set& operator=(const Set<Type> &S);   //assign the set
};

#endif