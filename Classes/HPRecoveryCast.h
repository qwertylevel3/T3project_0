#pragma once

#include "SkillBase.h"

namespace Skill
{
	class HPRecoveryCast:public SkillBase
	{
	public:
		HPRecoveryCast();
		~HPRecoveryCast();
		HPRecoveryCast* createPrototype();
	protected:
		void run();
		void initExtraMessage(std::vector<std::string> extraMessage);
		int value;
	};
}
