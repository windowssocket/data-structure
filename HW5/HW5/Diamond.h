/*
 *File:Diamond
 *Version:1.0
 *-------------------------------------------
 *Usage:it can draw a picture of a diamond
 *Remark:a combinition of class UpTriangle and InvTriangle
 */

#ifndef _Diamond_h
#define _Diamond_h

#include"Shape.h"
#include"UpTriangle.h"
#include"InvTriangle.h"
#include<iostream>
using namespace std;

class Diamond:public Shape
{
  public:
	  Diamond();
	  Diamond(int diagonal, int location);

	  virtual void Input();  //virtual function overloading, input the data of the diamond
	  virtual void Print()const;  //virtual function overloading, print the diamond

  private:
	  int diagonal;  //the length of the horizontal diagnonal
	  int location;  //the location of the diamond
};

#endif