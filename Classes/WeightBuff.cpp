#include "WeightBuff.h"
#include "Character.h"
#include "CharacterAttrHandler.h"
#include "ToolFunction.h"



Buff::WeightBuff::WeightBuff()
{
}


Buff::WeightBuff::~WeightBuff()
{
}

void Buff::WeightBuff::apply(Character* target)
{
	CharacterAttrHandler* attrHandler = target->getAttrHandler();
	attrHandler->setWeightByBuff(attrHandler->getWeight() + weightOffset);
}

Buff::WeightBuff* Buff::WeightBuff::createPrototype()
{
	return new WeightBuff();
}

void Buff::WeightBuff::initExtraMessage(std::vector<std::string> baseMessage)
{
	setWeightOffset(ToolFunction::string2int(baseMessage[0]));
}
