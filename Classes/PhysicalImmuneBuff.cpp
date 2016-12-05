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

std::string Buff::PhysicalImmuneBuff::getDescription()
{
	return ToolFunction::WStr2UTF8(L"ŒÔ¿Ì√‚“ﬂ");
}

void Buff::PhysicalImmuneBuff::initExtraMessage(std::vector<std::string> baseMessage)
{

}
