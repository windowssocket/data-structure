/*
 *File:Shape
 *Version:1.0
 *-------------------------------------------
 *Usage:it can draw a picture of a shape
 *Remark:abstract class, implement polymiorphism
 */

#ifndef _Shape_h
#define _Shape_h

class Shape
{
  public:
	  virtual void Input()=0;        //input the data of the shape
	  virtual void Print()const=0;   //print the shape
};


#endif