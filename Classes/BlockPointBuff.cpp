#include "BlockPointBuff.h"
#include "Character.h"
#include "CharacterAttrHandler.h"
#include "ToolFunction.h"



Buff::BlockPointBuff::BlockPointBuff()
{
}


Buff::BlockPointBuff::~BlockPointBuff()
{
}

void Buff::BlockPointBuff::apply(Character* target)
{
	CharacterAttrHandler* attrHandler = target->getAttrHandler();
	attrHandler->setBlockPointByBuff(attrHandler->getBlockPoint() + blockPointOffset);
}

Buff::BlockPointBuff* Buff::BlockPointBuff::createPrototype()
{
	BlockPointBuff* newBuff = new BlockPointBuff();
	return newBuff;
}

void Buff::BlockPointBuff::initExtraMessage(std::vector<std::string> baseMessage)
{
	setBlockPointOffset(ToolFunction::string2int(baseMessage[0]));
}
