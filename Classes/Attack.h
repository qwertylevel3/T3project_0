#pragma once

#include "SkillBase.h"

namespace Skill
{
	class Attack :public SkillBase
	{
	public:
		Attack();
		~Attack();
		Attack* createPrototype();
	protected:
		std::string getExtraDescription();
		void initExtraMessage(std::vector<std::string> extraMessage);
		void run();
	};
}
