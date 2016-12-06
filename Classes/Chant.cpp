#include "Chant.h"
#include "Character.h"
#include "FixedSelector.h"
#include "ToolFunction.h"

Skill::Chant::Chant()
{
	this->setCname(ToolFunction::WStr2UTF8(L"吟唱"));
	this->setChantCost(0);
	this->setMpCost(0);
}

Skill::Chant::~Chant()
{
}

Skill::Chant* Skill::Chant::createPrototype()
{
	return new Chant();
}

std::string  Skill::Chant::getExtraDescription()
{
	return ToolFunction::WStr2UTF8(L"效果:\n")
		+ ToolFunction::WStr2UTF8(L"增加吟唱点")
		+ ToolFunction::int2string(caster->getIntellect());
}

void Skill::Chant::initExtraMessage(std::vector<std::string> extraMessage)
{
	return;
}

void Skill::Chant::run()
{
	caster->accumulateChant(caster->getIntellect());
}
