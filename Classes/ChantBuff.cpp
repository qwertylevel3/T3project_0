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
	target->accumulateChant(addPer*target->getIntellect());
}

Buff::ChantBuff* Buff::ChantBuff::createPrototype()
{
	return new Buff::ChantBuff();
}

void Buff::ChantBuff::initExtraMessage(std::vector<std::string> baseMessage)
{
	setAddPer(ToolFunction::string2int(baseMessage[0]));
}
