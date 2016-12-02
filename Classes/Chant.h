#pragma once

#include "SkillBase.h"

namespace Skill
{
	class Chant :public SkillBase
	{
	public:
		Chant();
		~Chant();
		Chant* createPrototype();
	protected:
		void initExtraMessage(std::vector<std::string> extraMessage);
		void run();
	};
}
