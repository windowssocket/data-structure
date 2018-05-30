/*
 *File:UpTriangle
 *Version:1.0
 *-------------------------------------------
 *Usage:it can draw a picture of a upright isosceles triangle
 *Remark:inherit from class Shape
 */

#ifndef _UpTriangle_h
#define _UpTriangle_h

#include"Shape.h"
#include<iostream>
using namespace std;

class UpTriangle:public Shape
{
  public:
	  UpTriangle();
	  UpTriangle(int height, int location);

	  virtual void Input();    //virtual function overloading, input the data of the triangle
	  virtual void Print()const; //virtual function overloading, print the triangle
  
  protected:
	  int height;   //the height of the triangle
	  int location; //the location of the triangle


};

#endif