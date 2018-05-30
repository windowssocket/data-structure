#ifndef _text_h
#define _text_h

#include<iostream>
#include<fstream>
#include<list>
#include<string>
using namespace std;

class Text
{
	public:
		void Open(char *filename);
		void Quit(char *filename);
		void List(int n1, int n2);
		void del(int row, int col, int n);
		void ins(int row, int col, string str);

	private:
		list<string> txt;  //using list to save a line and using string to save every word per line 
};

#endif
