/*
 *File:GH_Random.h
 *Version:1.0
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


template<typename RandType>
RandType Random(RandType low, RandType high)   //generate random value in [low,high]
{
	return (high-low+1)*rand()/(RAND_MAX+1)+low;
}


template<typename RandType>
RandType* RandomLine(int length, RandType low, RandType high)   //generate array random
{
	RandType *tmp=new RandType[length+1];  //interim store random line

	for(int i=0; i<length; ++i) tmp[i]=Random(low,high);  //invoke Random()
	tmp[length]='\0';

	return tmp;
}


#endif