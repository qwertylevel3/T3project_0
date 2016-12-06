#include "ChantSelf.h"
#include "Character.h"
#include "ToolFunction.h"



Skill::ChantSelf::ChantSelf()
{
}


Skill::ChantSelf::~ChantSelf()
{
}

Skill::ChantSelf* Skill::ChantSelf::createPrototype()
{
	return new Skill::ChantSelf();
}

std::string Skill::ChantSelf::getExtraDescription()
{
	return ToolFunction::WStr2UTF8(L"效果:\n")
		+ ToolFunction::WStr2UTF8(L"增加吟唱点")
		+ ToolFunction::int2string(value);
}

void Skill::ChantSelf::run()
{
	caster->accumulateChant(value);
}

void Skill::ChantSelf::initExtraMessage(std::vector<std::string> extraMessage)
{
	value = ToolFunction::string2int(extraMessage[0]);
}
