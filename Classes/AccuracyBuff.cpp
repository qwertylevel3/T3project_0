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

void Buff::AccuracyBuff::initExtraMessage(std::vector<std::string> baseMessage)
{
	setAccuracyOffset(ToolFunction::string2int(baseMessage[0]));
}
