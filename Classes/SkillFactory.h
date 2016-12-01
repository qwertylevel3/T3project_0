#pragma once

#include "Singleton.h"
#include <string>
#include <vector>
#include <map>

class Character;


namespace Skill
{
	class SkillBase;

	class SkillFactory:public Singleton<SkillFactory>
	{
	public:
		SkillFactory();
		~SkillFactory();
		void init();
		SkillBase* getSkill(Character* character,std::string s);
	protected:
		SkillBase* getSkillPrototype(Character* character,const std::string& skillName);
		std::map<std::string, SkillBase*> skillPrototypeBox;
		void split(std::string s, char splitchar, std::vector<std::string>& vec);
	};
}
