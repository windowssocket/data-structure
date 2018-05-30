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
