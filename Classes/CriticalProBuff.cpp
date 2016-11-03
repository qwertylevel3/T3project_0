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

void Buff::CriticalProBuff::initExtraMessage(std::vector<std::string> baseMessage)
{
	setCriticalProOffset(ToolFunction::string2int(baseMessage[0]));
}
