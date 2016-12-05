#include "EvadeBuff.h"
#include "Character.h"
#include "CharacterAttrHandler.h"
#include "ToolFunction.h"


Buff::EvadeBuff::EvadeBuff()
{
}


Buff::EvadeBuff::~EvadeBuff()
{
}

void Buff::EvadeBuff::apply(Character* target)
{
	CharacterAttrHandler* attrHandler = target->getAttrHandler();
	attrHandler->setEvadePointByBuff(attrHandler->getEvadePoint() + evadeOffset);
}

Buff::EvadeBuff* Buff::EvadeBuff::createPrototype()
{
	EvadeBuff* newBuff = new EvadeBuff();
	return newBuff;
}

std::string Buff::EvadeBuff::getDescription()
{
	return ToolFunction::WStr2UTF8(L"ÉÁ±Ü¸ÅÂÊ")
		+(evadeOffset>0?"+":"")
		+ ToolFunction::int2string(evadeOffset);
}

void Buff::EvadeBuff::initExtraMessage(std::vector<std::string> baseMessage)
{
	setEvadeOffset(ToolFunction::string2int(baseMessage[0]));
}
