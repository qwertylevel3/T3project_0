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
		bool runSkill(int index);
		bool runSkill(const std::string& skillName);
		std::vector<SkillBase* >& getSkillBoxRef();
		void addSkill(SkillBase* skill);
		std::string getSkillName(int index);
	protected:
		std::vector<SkillBase* > skillBox;
	};
}
