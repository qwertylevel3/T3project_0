#include "AccuracyBuff.h"
#include "Character.h"
#include "CharacterAttrHandler.h"
#include "ToolFunction.h"



Buff::AccuracyBuff::AccuracyBuff()
{
}


Buff::AccuracyBuff::~AccuracyBuff()
{
}

void Buff::AccuracyBuff::apply(Character* target)
{
	CharacterAttrHandler* attrHandler = target->getAttrHandler();
	attrHandler->setAccuracyPointByBuff(attrHandler->getAccuracyPoint() + accuracyOffset);
}

Buff::AccuracyBuff* Buff::AccuracyBuff::createPrototype()
{
	AccuracyBuff* newBuff = new AccuracyBuff();
	return newBuff;
}

std::string Buff::AccuracyBuff::getDescription()
{
	return ToolFunction::WStr2UTF8(L"¹¥»÷ÃüÖÐÂÊ")
		+(accuracyOffset>0?"+":"")
		+ ToolFunction::int2string(accuracyOffset)
		+ "%";
}

void Buff::AccuracyBuff::initExtraMessage(std::vector<std::string> baseMessage)
{
	setAccuracyOffset(ToolFunction::string2int(baseMessage[0]));
}
