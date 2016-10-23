#include "ChantEffect.h"
#include "Character.h"



Skill::ChantEffect::ChantEffect()
{
}


Skill::ChantEffect::~ChantEffect()
{
}

bool Skill::ChantEffect::run(Character* caster, std::vector<cocos2d::Point>& coord)
{
	caster->accumulateChant(caster->getIntellect());
	return true;
}
