#ifndef _pascal_h
#define _pascal_h

#include<iostream>
#include<fstream>
#include<stack>
#include<string>
using namespace std;

class Pascal
{
	private:
		ifstream fin;

	public:
		void Open(char* filename){fin.open(filename);}
		bool CheckMatch(); //only can check once
};

#endif