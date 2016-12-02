#pragma once

#include "SkillBase.h"

namespace Skill
{
	class HPRecoveryCast:public SkillBase
	{
	public:
		HPRecoveryCast(Character* character);
		~HPRecoveryCast();
		HPRecoveryCast* createPrototype(Character* caster);
	protected:
		void run();
		void initExtraMessage(std::vector<std::string> extraMessage);
		int value;
	};
}
