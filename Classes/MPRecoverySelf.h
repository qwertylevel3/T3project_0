#pragma once

#include "SkillBase.h"

namespace Skill
{
	class MPRecoverySelf:public SkillBase
	{
	public:
		MPRecoverySelf(Character* character);
		~MPRecoverySelf();
		MPRecoverySelf* createPrototype(Character* caster);
	protected:
		void run();
		void initExtraMessage(std::vector<std::string> extraMessage);
		int value;
	};
}
