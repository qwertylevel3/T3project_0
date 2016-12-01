#include "Chant.h"
#include "Character.h"
#include "FixedSelector.h"
#include "ToolFunction.h"

Skill::Chant::Chant(Character* character)
	:SkillBase(character)
{
	this->setName("chant");
	this->setCname(ToolFunction::WStr2UTF8(L"Ò÷³ª"));
	this->setChantCost(0);
	this->setMpCost(0);
}

Skill::Chant::~Chant()
{
}

void Skill::Chant::run()
{
	caster->accumulateChant(caster->getIntellect());
}
