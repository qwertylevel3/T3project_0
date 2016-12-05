#include "MPBuff.h"
#include "Character.h"
#include "ToolFunction.h"



Buff::MPBuff::MPBuff()
{
	effectValue = 0;
}


Buff::MPBuff::~MPBuff()
{
}

void Buff::MPBuff::apply(Character* target)
{
	target->sufferMPEffect(effectValue);
}

Buff::MPBuff* Buff::MPBuff::createPrototype()
{
	MPBuff* newBuff = new MPBuff();
	return newBuff;
}

std::string Buff::MPBuff::getDescription()
{
	return ToolFunction::WStr2UTF8(L"每回合开始")
		+ (effectValue > 0 ? "+" : "")
		+ ToolFunction::int2string(effectValue);
}

void Buff::MPBuff::initExtraMessage(std::vector<std::string> baseMessage)
{
	effectValue = ToolFunction::string2int(baseMessage[0]);
}
