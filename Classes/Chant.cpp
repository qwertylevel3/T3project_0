#include "Chant.h"
#include "Character.h"
#include "FixedSelector.h"
#include "ToolFunction.h"

Skill::Chant::Chant()
{
	this->setCname(ToolFunction::WStr2UTF8(L"Ò÷³ª"));
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

void Skill::Chant::initExtraMessage(std::vector<std::string> extraMessage)
{
	return;
}

void Skill::Chant::run()
{
	caster->accumulateChant(caster->getIntellect());
}
