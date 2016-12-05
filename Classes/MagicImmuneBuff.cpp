#include "MagicImmuneBuff.h"
#include "Character.h"
#include "CharacterAttrHandler.h"
#include "ToolFunction.h"



Buff::MagicImmuneBuff::MagicImmuneBuff()
{
}


Buff::MagicImmuneBuff::~MagicImmuneBuff()
{
}

void Buff::MagicImmuneBuff::apply(Character* target)
{
	CharacterAttrHandler* attrHandler = target->getAttrHandler();
	attrHandler->setMagicImmuneByBuff(true);
}

Buff::MagicImmuneBuff* Buff::MagicImmuneBuff::createPrototype()
{
	return new MagicImmuneBuff();
}

std::string Buff::MagicImmuneBuff::getDescription()
{
	return ToolFunction::WStr2UTF8(L"Ä§·¨ÃâÒß");
}

void Buff::MagicImmuneBuff::initExtraMessage(std::vector<std::string> baseMessage)
{

}
