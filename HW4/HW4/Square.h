/*
 *File:Square
 *Version:1.0
 *-------------------------------------------
 *Usage:it can draw a picture of a square
 *Remark:inherit from class Rectangle
 */

#ifndef _Square_h
#define _Square_h

#include"Rectangle.h"
#include<iostream>
using namespace std;

class Square:public Rectangle
{
  public:
	  Square();
	  Square(int width, int location);

	  virtual void Input();  //virtual function overloading, input the data of the square
};

#endif