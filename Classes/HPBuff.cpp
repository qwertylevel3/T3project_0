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

void Buff::HPBuff::initExtraMessage(std::vector<std::string> baseMessage)
{
	effectValue = ToolFunction::string2int(baseMessage[0]);
}
