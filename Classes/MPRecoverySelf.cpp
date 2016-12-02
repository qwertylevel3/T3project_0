#include "MPRecoverySelf.h"
#include "ToolFunction.h"
#include "Character.h"



Skill::MPRecoverySelf::MPRecoverySelf()
{
}


Skill::MPRecoverySelf::~MPRecoverySelf()
{
}

Skill::MPRecoverySelf* Skill::MPRecoverySelf::createPrototype()
{
	return new MPRecoverySelf();
}

void Skill::MPRecoverySelf::run()
{
	caster->sufferMPEffect(value);
}

void Skill::MPRecoverySelf::initExtraMessage(std::vector<std::string> extraMessage)
{
	value = ToolFunction::string2int(extraMessage[0]);
}
