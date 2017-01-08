#include "ChantBuff.h"
#include "Character.h"
#include "ToolFunction.h"



Buff::ChantBuff::ChantBuff()
{
}


Buff::ChantBuff::~ChantBuff()
{
}

void Buff::ChantBuff::apply(Character* target)
{
	target->accumulateChant(addPer*target->getIntellect()/100);
}

Buff::ChantBuff* Buff::ChantBuff::createPrototype()
{
	return new Buff::ChantBuff();
}

std::string Buff::ChantBuff::getDescription()
{
	return ToolFunction::WStr2UTF8(L"每回合开始获得:")
		+ ToolFunction::int2string(addPer)
		+"%"
		+ "x"
		+ ToolFunction::WStr2UTF8(L"玩家智力 吟唱点");
}

void Buff::ChantBuff::initExtraMessage(std::vector<std::string> baseMessage)
{
	setAddPer(ToolFunction::string2int(baseMessage[0]));
}
