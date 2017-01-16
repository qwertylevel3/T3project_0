#pragma once

#include "SkillBase.h"
#include "Character.h"

namespace Skill
{
	class RandomDirectDamage :public SkillBase
	{
	public:
		RandomDirectDamage();
		~RandomDirectDamage();
		RandomDirectDamage* createPrototype();
	protected:
		std::string getExtraDescription();
		void run();
		void initExtraMessage(std::vector<std::string> extraMessage);
		Character* searchTargetBFS(Character::Type type);

		int damagePre;
		int distance;
		Character::Type targetType;
	};
}
