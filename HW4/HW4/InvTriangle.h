/*
 *File:InvTriangle
 *Version:1.0
 *-------------------------------------------
 *Usage:it can draw a picture of a inverted isosceles triangle
 *Remark:inherit from class UpTriangle
 */

#ifndef _InvTriangle_h
#define _InvTriangle_h

#include"UpTriangle.h"
#include<iostream>
using namespace std;

class InvTriangle:public UpTriangle
{
  public:
	  InvTriangle();
	  InvTriangle(int height, int location);
	  virtual void Print()const; //virtual function overloading, print the triangle

};

#endif