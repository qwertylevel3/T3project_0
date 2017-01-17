#pragma once

#include "SkillBase.h"

namespace Skill
{
	class HPCastAccordInt :public SkillBase
	{
	public:
		HPCastAccordInt();
		~HPCastAccordInt();
		HPCastAccordInt* createPrototype();
	protected:
		std::string getExtraDescription();
		void run();
		void initExtraMessage(std::vector<std::string> extraMessage);
		int valuePer;
	};
}
