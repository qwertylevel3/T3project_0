#pragma once

#include "SkillBase.h"

namespace Skill
{
	class Thunder:public SkillBase
	{
	public:
		Thunder();
		~Thunder();
		Thunder* createPrototype();
	protected:
		std::string getExtraDescription();
		void run();
		void initExtraMessage(std::vector<std::string> extraMessage);

		int damagePer;
	};
}
