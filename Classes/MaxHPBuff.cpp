#include "MaxHPBuff.h"
#include "Character.h"
#include "CharacterAttrHandler.h"
#include "ToolFunction.h"



Buff::MaxHPBuff::MaxHPBuff()
{
}


Buff::MaxHPBuff::~MaxHPBuff()
{
}

void Buff::MaxHPBuff::apply(Character* target)
{
	CharacterAttrHandler* attrHandler = target->getAttrHandler();
	attrHandler->setMaxHPByBuff(maxHPOffset + attrHandler->getMaxHP());
}

Buff::MaxHPBuff* Buff::MaxHPBuff::createPrototype()
{
	MaxHPBuff* newBuff = new MaxHPBuff();
	return newBuff;
}

void Buff::MaxHPBuff::initExtraMessage(std::vector<std::string> baseMessage)
{
	setMaxHPOffset(ToolFunction::string2int(baseMessage[0]));
}
