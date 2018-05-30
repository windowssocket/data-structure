/*
 *File:Polygon
 *Version:1.0
 *-------------------------------------------
 *Usage:it can draw a picture of a polygon
 *Remark:a combinition of class UpTriangle and Rectangle
 */

#ifndef _Polygon_h
#define _Polygon_h

#include"Shape.h"
#include"UpTriangle.h"
#include"Rectangle.h"
#include<iostream>
using namespace std;

class Polygon:public Shape
{
  public:
	  Polygon();
	  Polygon(int width, int location);

	  virtual void Input();  //virtual function overloading, input the data of the polygon
	  virtual void Print()const;  //virtual function overloading, print the polygon

  private:
	  int width;    //the width of the polygon
	  int location; //the location of the polygon
};

#endif