#include "Supply.h"
#include "Character.h"



Supply::Supply()
{
	setInventoryType(Inventory::Supply);
}


Supply::~Supply()
{
}

Supply* Supply::clone()
{
	Supply* newSupply = new Supply();
	copyData(newSupply);
	newSupply->setSkillName(this->getSkillName());
	newSupply->setStrRequire(strRequire);
	newSupply->setAgiRequire(agiRequire);
	newSupply->setIntRequire(intRequire);
	newSupply->setSupplyType(supplyType);
	return newSupply;
}

void Supply::use(Character* character)
{
	character->runSkill(skillName);
}

void Supply::setSupplyType(int typeID)
{
	if (typeID==0)
	{
		supplyType = HPSupply;
	}
	else if (typeID==1)
	{
		supplyType = MPSupply;
	}
	else if (typeID==2)
	{
		supplyType = OtherSupply;
	}
	else
	{
		supplyType = OtherSupply;
	}
}
