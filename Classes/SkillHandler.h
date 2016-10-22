#pragma once

#include "SkillBase.h"
#include <vector>

namespace Skill
{
	class SkillHandler
	{
	public:
		SkillHandler();
		~SkillHandler();
		void runSkill(int index);
		void runSkill(const std::string& skillName);
		std::vector<SkillBase* >& getSkillBoxRef();
		void addSkill(SkillBase* skill);
	protected:
		std::vector<SkillBase* > skillBox;
	};
}
