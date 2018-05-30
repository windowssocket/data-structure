/*
 *File:GH_Random.h
 *Version:2.1
 *-------------------------------------------
 *Usage:generate random values
 *Remark:a library include some func
 */

#ifndef _GH_Random_h
#define _GH_Random_h

#include<cstdlib>
#include<ctime>

unsigned int RandomInit(unsigned int seed=(unsigned int)time(NULL));   //initialize random
unsigned int GetRandSeed();   //get the random seed currently

int Random(int low, int high);            //generate random value in [low,high]
double Random(double low, double high);   //generate random value in [low,high]
char Random(char low, char high);         //generate random value in [low,high]

int RandomChoose(int totalElem, int elem,...);            //generate random value elem in elem1,elem2,...
double RandomChoose(int totalElem, double elem,...);   //generate random value elem in elem1,elem2,...
char RandomChoose(int totalElem, char elem,...);            //generate random value elem in elem1,elem2,...

char* RandomLine(int length, char low, char high);   //generate array random

#endif