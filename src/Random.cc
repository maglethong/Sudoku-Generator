#include "Random.h"



Random::Random()
{
	this->genCount = 0;
	this->seed = time(0);
	srand(this->seed);	
}

Random::Random(long seed)
{
	this->genCount = 0;
	this->seed = seed;
	srand(seed);
}

Random::~Random(){}


int Random::nextInt()
{
	this->genCount++;
	return random();	
}

int Random::nextInt(int min, int max)
{
	this->genCount++;
	return random()%(max -min +1) +min;
}


int Random::getSeed()
{
	return this->seed;
}

int Random::getGenCount()
{
	return this->genCount;
}

