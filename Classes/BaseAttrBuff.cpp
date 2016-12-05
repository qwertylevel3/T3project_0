#include "BaseAttrBuff.h"
#include "Character.h"
#include "CharacterAttrHandler.h"
#include "ToolFunction.h"

Buff::BaseAttrBuff::BaseAttrBuff()
{
	strOffset = 0;
	agiOffset = 0;
	intOffset = 0;
}

Buff::BaseAttrBuff::~BaseAttrBuff()
{
}

void Buff::BaseAttrBuff::apply(Character* target)
{
	CharacterAttrHandler* attrHandler = target->getAttrHandler();

	attrHandler->setStrengthByBuff(strOffset + attrHandler->getStrength());
	attrHandler->setAgilityByBuff(agiOffset + attrHandler->getAgility());
	attrHandler->setIntellectByBuff(intOffset + attrHandler->getIntellect());
}

Buff::BaseAttrBuff* Buff::BaseAttrBuff::createPrototype()
{
	BaseAttrBuff* newBuff = new BaseAttrBuff();
	return newBuff;
}

std::string Buff::BaseAttrBuff::getDescription()
{
	return ToolFunction::WStr2UTF8(L"基础属性:\n")
		+(strOffset>0?"+":"")
		+ ToolFunction::int2string(strOffset) + ToolFunction::WStr2UTF8(L"力量\n")
		+(agiOffset>0?"+":"")
		+ ToolFunction::int2string(agiOffset) + ToolFunction::WStr2UTF8(L"敏捷\n")
		+(intOffset>0?"+":"")
		+ ToolFunction::int2string(intOffset) + ToolFunction::WStr2UTF8(L"智力\n");
}

void Buff::BaseAttrBuff::initExtraMessage(std::vector<std::string> baseMessage)
{
	setStrOffset(ToolFunction::string2int(baseMessage[0]));
	setAgiOffset(ToolFunction::string2int(baseMessage[1]));
	setIntOffset(ToolFunction::string2int(baseMessage[2]));
}