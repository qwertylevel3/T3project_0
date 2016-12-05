#include "ComboBuff.h"
#include "Character.h"
#include "CharacterAttrHandler.h"
#include "ToolFunction.h"



Buff::ComboBuff::ComboBuff()
{
}


Buff::ComboBuff::~ComboBuff()
{
}

void Buff::ComboBuff::apply(Character* target)
{
	CharacterAttrHandler* attrHandler = target->getAttrHandler();
	attrHandler->setComboProByBuff(attrHandler->getComboPro() + comboOffset);
}

Buff::ComboBuff* Buff::ComboBuff::createPrototype()
{
	return new Buff::ComboBuff;
}

std::string Buff::ComboBuff::getDescription()
{
	return ToolFunction::WStr2UTF8(L"Á¬»÷¸ÅÂÊ")
		+(comboOffset>0?"+":"")
		+ ToolFunction::int2string(comboOffset) + "%";
}

void Buff::ComboBuff::initExtraMessage(std::vector<std::string> baseMessage)
{
	setComboOffset(ToolFunction::string2int(baseMessage[0]));
}
