#include "CriticalProBuff.h"
#include "Character.h"
#include "CharacterAttrHandler.h"
#include "ToolFunction.h"



Buff::CriticalProBuff::CriticalProBuff()
{
}


Buff::CriticalProBuff::~CriticalProBuff()
{
}

void Buff::CriticalProBuff::apply(Character* target)
{
	CharacterAttrHandler* attrHandler = target->getAttrHandler();
	attrHandler->setCriticalProByBuff(attrHandler->getCriticalPro() + criticalProOffset);
}

Buff::CriticalProBuff * Buff::CriticalProBuff::createPrototype()
{
	CriticalProBuff* newBuff = new CriticalProBuff();
	return newBuff;
}

std::string Buff::CriticalProBuff::getDescription()
{
	return ToolFunction::WStr2UTF8(L"±©»÷¸ÅÂÊ")
		+(criticalProOffset>0?"+":"") 
		+ ToolFunction::int2string(criticalProOffset) + "%";
}

void Buff::CriticalProBuff::initExtraMessage(std::vector<std::string> baseMessage)
{
	setCriticalProOffset(ToolFunction::string2int(baseMessage[0]));
}
