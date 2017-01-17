#pragma once

#include "SkillBase.h"

namespace Skill
{
	class HPSelfAccordInt:public SkillBase
	{
	public:
		HPSelfAccordInt();
		~HPSelfAccordInt();
		HPSelfAccordInt* createPrototype();
	protected:
		std::string getExtraDescription();
		void run();
		void initExtraMessage(std::vector<std::string> extraMessage);
		int valuePer;
	};
}
