#include "CriticalPerBuff.h"
#include "Character.h"
#include "CharacterAttrHandler.h"
#include "ToolFunction.h"



Buff::CriticalPerBuff::CriticalPerBuff()
{
}


Buff::CriticalPerBuff::~CriticalPerBuff()
{
}

void Buff::CriticalPerBuff::apply(Character* target)
{
	CharacterAttrHandler* attrHandler = target->getAttrHandler();
	attrHandler->setCriticalPerByBuff(attrHandler->getCriticalPer()+criticalPerOffset);
}

Buff::CriticalPerBuff* Buff::CriticalPerBuff::createPrototype()
{
	CriticalPerBuff* newBuff = new CriticalPerBuff();
	return newBuff;
}

void Buff::CriticalPerBuff::initExtraMessage(std::vector<std::string> baseMessage)
{
	setCriticalPerOffset(ToolFunction::string2int(baseMessage[0]));
}
