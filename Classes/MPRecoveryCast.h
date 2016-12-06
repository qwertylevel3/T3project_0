#pragma once

#include "SkillBase.h"

namespace Skill
{
	class MPRecoveryCast:public SkillBase
	{
	public:
		MPRecoveryCast();
		~MPRecoveryCast();
		MPRecoveryCast* createPrototype();
	protected:
		std::string getExtraDescription();
		void run();
		void initExtraMessage(std::vector<std::string> extraMessage);
		int value;
	};
}
