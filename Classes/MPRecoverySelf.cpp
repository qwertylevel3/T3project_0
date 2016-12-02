#include "MPRecoverySelf.h"
#include "ToolFunction.h"
#include "Character.h"



Skill::MPRecoverySelf::MPRecoverySelf(Character* character)
	:SkillBase(character)
{
}


Skill::MPRecoverySelf::~MPRecoverySelf()
{
}

Skill::MPRecoverySelf* Skill::MPRecoverySelf::createPrototype(Character* caster)
{
	return new MPRecoverySelf(caster);
}

void Skill::MPRecoverySelf::run()
{
	caster->sufferMPEffect(value);
}

void Skill::MPRecoverySelf::initExtraMessage(std::vector<std::string> extraMessage)
{
	value = ToolFunction::string2int(extraMessage[0]);
}
