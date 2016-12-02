#pragma once

#include "SkillBase.h"

namespace Skill
{
	class HPRecoverySelf:public SkillBase
	{
	public:
		HPRecoverySelf(Character* character);
		~HPRecoverySelf();
		HPRecoverySelf* createPrototype(Character* caster);
	protected:
		void run();
		void initExtraMessage(std::vector<std::string> extraMessage);
		int value;
	};
}
