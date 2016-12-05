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

std::string Buff::BlockPointBuff::getDescription()
{
	return ToolFunction::WStr2UTF8(L"¸ñµ²µãÊý")
		+(blockPointOffset>0?"+":"")
		+ ToolFunction::int2string(blockPointOffset);
}

void Buff::BlockPointBuff::initExtraMessage(std::vector<std::string> baseMessage)
{
	setBlockPointOffset(ToolFunction::string2int(baseMessage[0]));
}
