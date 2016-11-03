#include "MagicImmuneBuff.h"
#include "Character.h"
#include "CharacterAttrHandler.h"



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

void Buff::MagicImmuneBuff::initExtraMessage(std::vector<std::string> baseMessage)
{

}
