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
	nextSkill = nullptr;
	mpCost = 0;
}

SkillBase::~SkillBase()
{
	delete selector;
	delete nextSkill;
}

void Skill::SkillBase::addEffect(EffectBase* effect)
{
	effectBox.push_back(effect);
}

void Skill::SkillBase::active()
{
	if (caster->getMP() < mpCost)
	{
		return;
	}
	else
	{
		caster->sufferMPEffect(-mpCost);
	}

	std::vector<cocos2d::Point> targetPositionVec;
	if (selector)
	{
		targetPositionVec = selector->select(caster);
	}

	for each (EffectBase* effect in effectBox)
	{
		effect->run(caster, targetPositionVec);
	}
}
