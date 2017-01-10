#pragma once

#include "Inventory.h"
#include <string>

class Note:public Inventory
{
public:
	Note();
	~Note();
	Note* clone();
protected:
	CC_SYNTHESIZE(std::string, textID, TextID);
};

