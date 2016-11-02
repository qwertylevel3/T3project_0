#include "DogTag.h"
#include "DogTagGenerator.h"



DogTag::DogTag()
{
	number = DogTagGenerator::getInstance()->genNumber();
}


DogTag::~DogTag()
{
}

int DogTag::getNumber()
{
	return number;
}
