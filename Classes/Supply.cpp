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
	return newSupply;
}

void Supply::use(Character* character)
{
	character->runSkill(skillName);
}
