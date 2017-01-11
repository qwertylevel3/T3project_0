#pragma once

#include"Inventory.h"

class Supply:public Inventory
{
public:
	enum SupplyType
	{
		HPSupply,MPSupply,OtherSupply
	};
	Supply();
	~Supply();
	Supply* clone();
	void use(Character* character);
	void setSupplyType(int typeID);
protected:
	CC_SYNTHESIZE(std::string, skillName, SkillName);
	CC_SYNTHESIZE(int, strRequire, StrRequire);
	CC_SYNTHESIZE(int, agiRequire, AgiRequire);
	CC_SYNTHESIZE(int, intRequire, IntRequire);
	CC_SYNTHESIZE(SupplyType,supplyType,SupplyType)
};

