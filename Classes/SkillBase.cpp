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
	effector = nullptr;
	nextSkill = nullptr;
}


SkillBase::~SkillBase()
{
}

void Skill::SkillBase::active()
{
	std::vector<cocos2d::Point> targetPositionVec;
	if (selector)
	{
		targetPositionVec = selector->select(caster);
	}

	if (effector)
	{
		effector->run(caster,targetPositionVec);
	}
	if (nextSkill)
	{
		nextSkill->active();
	}
}
