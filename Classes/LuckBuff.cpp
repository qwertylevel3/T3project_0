#include "LuckBuff.h"
#include "Character.h"
#include "CharacterAttrHandler.h"
#include "ToolFunction.h"



Buff::LuckBuff::LuckBuff()
{
}


Buff::LuckBuff::~LuckBuff()
{
}

void Buff::LuckBuff::apply(Character* target)
{
	CharacterAttrHandler* attrHandler = target->getAttrHandler();
	attrHandler->setLuckByBuff(luckOffset + attrHandler->getLuck());
}

Buff::LuckBuff* Buff::LuckBuff::createPrototype()
{
	LuckBuff* newBuff = new LuckBuff();
	return newBuff;
}

std::string Buff::LuckBuff::getDescription()
{
	return ToolFunction::WStr2UTF8(L"幸运值提高")
		+ ToolFunction::int2string(luckOffset);
}

void Buff::LuckBuff::initExtraMessage(std::vector<std::string> baseMessage)
{
	setLuckOffset(ToolFunction::string2int(baseMessage[0]));
}
