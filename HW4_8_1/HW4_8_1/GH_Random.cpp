#include"GH_Random.h"


static unsigned int randSeed=RandomInit();  //the seed of random and initialize the random at beginning

unsigned int RandomInit(unsigned int seed)
{
	randSeed=seed;
	srand(randSeed);
	rand();
	return randSeed;
}


unsigned int GetRandSeed()
{
	return randSeed;
}


int Random(int low, int high)   //generate random value in [low,high]
{
	return (high-low+1)*rand()/(RAND_MAX+1)+low;
}


double Random(double low, double high)   //generate random value in [low,high]
{
	return (high-low)*rand()/RAND_MAX+low;
}


char Random(char low, char high)   //generate random value in [low,high]
{
	return (high-low+1)*rand()/(RAND_MAX+1)+low;
}


int RandomChoose(int totalElem, int elem,...)   //generate random value elem in elem1,elem2,...
{
	return *(&elem+Random(0,totalElem-1));
}


double RandomChoose(int totalElem, double elem,...)   //generate random value elem in elem1,elem2,...
{
	return *(&elem+Random(0,totalElem-1));
}


char RandomChoose(int totalElem, char elem,...)   //generate random value elem in elem1,elem2,...
{
	return *((int*)&elem+Random(0,totalElem-1));
}


char* RandomLine(int length, char low, char high)   //generate array random
{
	char *tmp=new char[length+1];  //interim store random line

	for(int i=0; i<length; ++i) tmp[i]=Random(low,high);  //invoke Random()
	tmp[length]='\0';

	return tmp;
}