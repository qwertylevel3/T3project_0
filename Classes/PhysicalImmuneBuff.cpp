#include "PhysicalImmuneBuff.h"
#include "Character.h"
#include "CharacterAttrHandler.h"
#include "ToolFunction.h"



Buff::PhysicalImmuneBuff::PhysicalImmuneBuff()
{
}


Buff::PhysicalImmuneBuff::~PhysicalImmuneBuff()
{
}

void Buff::PhysicalImmuneBuff::apply(Character* target)
{
	CharacterAttrHandler* attrHandler = target->getAttrHandler();
	attrHandler->setPhysicalImmnueByBuff(true);
}

Buff::PhysicalImmuneBuff* Buff::PhysicalImmuneBuff::createPrototype()
{
	return new Buff::PhysicalImmuneBuff();
}

void Buff::PhysicalImmuneBuff::initExtraMessage(std::vector<std::string> baseMessage)
{

}
