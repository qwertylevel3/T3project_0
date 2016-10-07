#pragma once

#include "base/ccMacros.h"
#include <string>

namespace Skill
{
	class SelectorBase;
	class RunnerBase;

	class SkillBase
	{
	public:
		SkillBase();
		virtual ~SkillBase();
	protected:
		CC_SYNTHESIZE(std::string, name, Name);

		CC_SYNTHESIZE(SelectorBase*, selector, Selector);
		CC_SYNTHESIZE(RunnerBase*, runner, Runner);
		CC_SYNTHESIZE(SkillBase*, childSill, ChildSkill);
		void active();
	};
}
