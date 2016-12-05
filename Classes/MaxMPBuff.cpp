#include "MaxMPBuff.h"
#include "Character.h"
#include "CharacterAttrHandler.h"
#include "ToolFunction.h"



Buff::MaxMPBuff::MaxMPBuff()
{
}


Buff::MaxMPBuff::~MaxMPBuff()
{
}

void Buff::MaxMPBuff::apply(Character* target)
{
	CharacterAttrHandler* attrHandler = target->getAttrHandler();
	attrHandler->setMaxMPByBuff(attrHandler->getMaxMP() + maxMPOffset);
}

Buff::MaxMPBuff* Buff::MaxMPBuff::createPrototype()
{
	MaxMPBuff* newBuff = new MaxMPBuff();
	return newBuff;
}

std::string Buff::MaxMPBuff::getDescription()
{

	return ToolFunction::WStr2UTF8(L"魔法值上限")
		+ (maxMPOffset > 0 ? "+" : "")
		+ ToolFunction::int2string(maxMPOffset);
}

void Buff::MaxMPBuff::initExtraMessage(std::vector<std::string> baseMessage)
{
	setMaxMPOffset(ToolFunction::string2int(baseMessage[0]));
}
