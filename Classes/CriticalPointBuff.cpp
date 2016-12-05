#include "CriticalPointBuff.h"
#include "Character.h"
#include "CharacterAttrHandler.h"
#include "ToolFunction.h"



Buff::CriticalPointBuff::CriticalPointBuff()
{
}


Buff::CriticalPointBuff::~CriticalPointBuff()
{
}

void Buff::CriticalPointBuff::apply(Character* target)
{
	CharacterAttrHandler* attrHandler = target->getAttrHandler();
	attrHandler->setCriticalPointByBuff(attrHandler->getCriticalPoint()+criticalPointOffset);
}

Buff::CriticalPointBuff* Buff::CriticalPointBuff::createPrototype()
{
	CriticalPointBuff* newBuff = new CriticalPointBuff();
	return newBuff;
}

std::string Buff::CriticalPointBuff::getDescription()
{
	return ToolFunction::WStr2UTF8(L"±©»÷ÉËº¦")
		+(criticalPointOffset>0?"+":"")
		+ ToolFunction::int2string(criticalPointOffset);
}

void Buff::CriticalPointBuff::initExtraMessage(std::vector<std::string> baseMessage)
{
	setCriticalPointOffset(ToolFunction::string2int(baseMessage[0]));
}
