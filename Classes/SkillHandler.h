#pragma once

#include "SkillBase.h"
#include <vector>

namespace Skill
{
	class SkillHandler
	{
	public:
		SkillHandler(Character* character);
		~SkillHandler();
		bool runSkill(int index);
		bool runSkill(const std::string& skillName);
		std::vector<SkillBase* >& getSkillBoxRef();
		void addSkill(SkillBase* skill);
		std::string getSkillID(int index);
	protected:
		Character* characterPtr;
		std::vector<SkillBase* > skillBox;
	};
}
