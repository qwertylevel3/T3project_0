#pragma once

#include"Singleton.h"
#include<random>

class RandomNumber:public Singleton<RandomNumber>
{
public:
	RandomNumber();
	~RandomNumber();
	void setSeed(int seed);
	int randomInt(int exclusiveMax);
	int randomInt(int min, int max);
	bool randomBool(double probability = 0.5);
private:
	std::mt19937 mt;
};

