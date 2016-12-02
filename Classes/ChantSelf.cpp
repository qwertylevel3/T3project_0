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

void Skill::ChantSelf::run()
{
	caster->accumulateChant(value);
}

void Skill::ChantSelf::initExtraMessage(std::vector<std::string> extraMessage)
{
	value = ToolFunction::string2int(extraMessage[0]);
}
