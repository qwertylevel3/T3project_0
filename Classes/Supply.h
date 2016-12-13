#pragma once

#include"Inventory.h"

class Supply:public Inventory
{
public:
	Supply();
	~Supply();
	Supply* clone();
	void use(Character* character);
protected:
	CC_SYNTHESIZE(std::string, skillName, SkillName);
	CC_SYNTHESIZE(int, strRequire, StrRequire);
	CC_SYNTHESIZE(int, agiRequire, AgiRequire);
	CC_SYNTHESIZE(int, intRequire, IntRequire);
};

