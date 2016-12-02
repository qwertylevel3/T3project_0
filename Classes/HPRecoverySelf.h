#pragma once

#include "SkillBase.h"

namespace Skill
{
	class HPRecoverySelf:public SkillBase
	{
	public:
		HPRecoverySelf();
		~HPRecoverySelf();
		HPRecoverySelf* createPrototype();
	protected:
		void run();
		void initExtraMessage(std::vector<std::string> extraMessage);
		int value;
	};
}
