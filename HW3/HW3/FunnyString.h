/*
 *File:FunnyString.h
 *Version:1.0
 *-------------------------------------------
 *Usage:a kind of string
 *Remark:just for fun, no usage
 */

#ifndef _FunnyString_h
#define _FunnyString_h

#include<iostream>
using namespace std;


class FunnyString
{
  public:
	  FunnyString();        //constructor
	  FunnyString(char*);   //constructor
	  FunnyString(FunnyString&);  //copy constructor
	  ~FunnyString();       //destructor

	  int Length()const;    //get the lenght of the string, '\0'is not included

	  FunnyString& operator=(const FunnyString&);   //operator=  overloading
	  FunnyString& operator+=(const FunnyString&);  //operator+= overloading
	  FunnyString& operator-=(const FunnyString&);  //operator-= overloading
	  FunnyString& operator*=(const FunnyString&);  //operator*= overloading

	  friend istream& operator>>(istream&, FunnyString&);        //operator>> overloading
	  friend ostream& operator<<(ostream&, const FunnyString&);  //operator<< overloading

	  friend FunnyString operator+(const FunnyString&, const FunnyString&);  //operator+ overloading
	  friend FunnyString operator-(const FunnyString&, const FunnyString&);  //operator- overloading
	  friend FunnyString operator*(const FunnyString&, const FunnyString&);  //operator* overloading

  private:
	  char *code;   //store the code of the string
	  int length;   //the lenght of the string

};


#endif