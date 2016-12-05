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

std::string Buff::WeightBuff::getDescription()
{
	return ToolFunction::WStr2UTF8(L"¸ºÖØ")
		+ (weightOffset > 0 ? "+" : "")
		+ ToolFunction::int2string(weightOffset);
}

void Buff::WeightBuff::initExtraMessage(std::vector<std::string> baseMessage)
{
	setWeightOffset(ToolFunction::string2int(baseMessage[0]));
}
