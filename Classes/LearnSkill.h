#pragma once

#include "SkillBase.h"

namespace Skill
{
	class LearnSkill:public SkillBase
	{
	public:
		LearnSkill();
		~LearnSkill();
		LearnSkill* createPrototype();
	protected:
		void run();
		void initExtraMessage(std::vector<std::string> extraMessage);
		std::string getExtraDescription();

		std::string skillID;
	};
}
