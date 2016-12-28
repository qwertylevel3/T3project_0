#pragma once

#include "SkillBase.h"

namespace Skill
{
	class ExpAdd:public SkillBase
	{
	public:
		ExpAdd();
		~ExpAdd();
		ExpAdd* createPrototype();
	protected:
		void run();
		void initExtraMessage(std::vector<std::string> extraMessage);
		virtual std::string getExtraDescription();
		int value;
	};
}
