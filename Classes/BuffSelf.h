#pragma once

#include "SkillBase.h"
#include <string>

namespace Skill
{
	class BuffSelf:public SkillBase
	{
	public:
		BuffSelf();
		~BuffSelf();
		BuffSelf* createPrototype();
	protected:
		std::string getExtraDescription();
		void run();
		void initExtraMessage(std::vector<std::string> extraMessage);

		std::string buffID;
	};
}
