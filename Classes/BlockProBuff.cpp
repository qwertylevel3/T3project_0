#include "BlockProBuff.h"
#include "Character.h"
#include "CharacterAttrHandler.h"
#include "ToolFunction.h"



Buff::BlockProBuff::BlockProBuff()
{
}


Buff::BlockProBuff::~BlockProBuff()
{
}

void Buff::BlockProBuff::apply(Character* target)
{
	CharacterAttrHandler* attrHandler = target->getAttrHandler();
	attrHandler->setBlockProByBuff(attrHandler->getBlockPro() + blockProOffset);
}

Buff::BlockProBuff* Buff::BlockProBuff::createPrototype()
{
	BlockProBuff* newBuff = new BlockProBuff();
	return newBuff;
}

void Buff::BlockProBuff::initExtraMessage(std::vector<std::string> baseMessage)
{
	setBlockProOffset(ToolFunction::string2int(baseMessage[0]));
}
