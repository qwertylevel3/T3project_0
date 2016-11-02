#include "DogTagGenerator.h"



DogTagGenerator::DogTagGenerator()
{
	curIndex = 0;
}


DogTagGenerator::~DogTagGenerator()
{
}

int DogTagGenerator::genNumber()
{
	return curIndex++;
}
