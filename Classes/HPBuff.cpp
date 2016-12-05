#include "HPBuff.h"
#include "Character.h"
#include "ToolFunction.h"



Buff::HPBuff::HPBuff()
{
	effectValue = 0;
}


Buff::HPBuff::~HPBuff()
{
}

void Buff::HPBuff::apply(Character* target)
{
	target->sufferHPEffect(effectValue);
}

Buff::HPBuff* Buff::HPBuff::createPrototype()
{
	Buff::HPBuff* newBuff = new Buff::HPBuff();
	return newBuff;
}

std::string Buff::HPBuff::getDescription()
{
	if (effectValue>0)
	{
		return ToolFunction::WStr2UTF8(L"每回合开始:HP")
			+ "+" + ToolFunction::int2string(effectValue);
	}
	else
	{
		return ToolFunction::WStr2UTF8(L"每回合开始:HP")
			+ ToolFunction::int2string(effectValue);
	}

		
}

void Buff::HPBuff::initExtraMessage(std::vector<std::string> baseMessage)
{
	effectValue = ToolFunction::string2int(baseMessage[0]);
}
