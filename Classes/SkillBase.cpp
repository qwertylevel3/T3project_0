#include "SkillBase.h"
#include "SelectorBase.h"
#include "EffectBase.h"
#include "base/ccTypes.h"
#include <vector>

using namespace Skill;

SkillBase::SkillBase(Character* character)
{
	caster = character;
	selector = nullptr;
	mpCost = 0;
	chantCost = 0;
}

SkillBase::~SkillBase()
{
	delete selector;
}

void Skill::SkillBase::addEffect(EffectBase* effect)
{
	effectBox.push_back(effect);
}

bool Skill::SkillBase::active()
{
	if (chantCost>caster->getChant() || mpCost>caster->getMP())
	{
		return false;
	}
	caster->consumeChant(chantCost);
	caster->consumeMP(mpCost);

	std::vector<cocos2d::Point> targetPositionVec;
	if (selector)
	{
		targetPositionVec = selector->select(caster);
	}
	for each (EffectBase* effect in effectBox)
	{
		effect->run(caster, targetPositionVec);
	}
	return true;
}
