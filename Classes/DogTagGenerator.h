#pragma once


#include "Singleton.h"

class DogTagGenerator:public Singleton<DogTagGenerator>
{
public:
	DogTagGenerator();
	~DogTagGenerator();
	int genNumber();
protected:
	int curIndex;
};

