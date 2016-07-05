#include "RandomNumber.h"



RandomNumber::RandomNumber()
{
}


RandomNumber::~RandomNumber()
{
}

void RandomNumber::setSeed(int seed)
{
	mt.seed(seed);
}

int RandomNumber::randomInt(int exclusiveMax)
{
	std::uniform_int_distribution<> dist(0, exclusiveMax - 1);
	return dist(mt);
}

int RandomNumber::randomInt(int min, int max)
{
	std::uniform_int_distribution<> dist(0, max - min);
	return dist(mt) + min;
}

bool RandomNumber::randomBool(double probability)
{
	std::bernoulli_distribution dist(probability);
	return dist(mt);
}
