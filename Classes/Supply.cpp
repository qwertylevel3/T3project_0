#include "Supply.h"
#include "ToolFunction.h"
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
		supplyType = MagicSupply;
	}
	else if (typeID==3)
	{
		supplyType = OtherSupply;
	}
}

std::string Supply::getExtraDescription()
{
	if (supplyType==MagicSupply)
	{
		return ToolFunction::WStr2UTF8(L"÷«¡¶–Ë«Û£∫") +
			ToolFunction::int2string(intRequire);
	}
	else
	{
		return "";
	}
}
