#pragma once

#include "SkillBase.h"

namespace Skill
{
	class Chant :public SkillBase
	{
	public:
		Chant(Character* character);
		~Chant();
		Chant* createPrototype(Character* caster);
	protected:
		void initExtraMessage(std::vector<std::string> extraMessage);
		void run();
	};
}
