#include "SkillBase.h"
#include "SelectorBase.h"
#include "RunnerBase.h"
#include "base/ccTypes.h"
#include <vector>


using namespace Skill;

SkillBase::SkillBase()
{
	selector = nullptr;
	runner = nullptr;
	childSkill = nullptr;
}


SkillBase::~SkillBase()
{
}

void Skill::SkillBase::active()
{
	std::vector<cocos2d::Point> targetPositionVec;
	if (selector)
	{
		targetPositionVec = selector->select();
	}

	if (runner)
	{
		runner->run(targetPositionVec);
	}
	if (childSkill)
	{
		childSkill->active();
	}
}
