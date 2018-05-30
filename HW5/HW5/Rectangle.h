/*
 *File:Rectangle
 *Version:1.0
 *-------------------------------------------
 *Usage:it can draw a picture of a rectangle
 *Remark:inherit from class Shape
 */

#ifndef _Rectangle_h
#define _Rectangle_h

#include"Shape.h"
#include<iostream>
using namespace std;

class Rectangle:public Shape
{
  public:
	  Rectangle();
	  Rectangle(int height, int width, int location);

	  virtual void Input();  //virtual function overloading, input the data of the rectangle
	  virtual void Print()const;  //virtual function overloading, print the shape

  protected:
	  int height;   //the height of the rectangle
	  int width;    //the width of the rectangle
	  int location; //the location of the rectangle
};

#endif