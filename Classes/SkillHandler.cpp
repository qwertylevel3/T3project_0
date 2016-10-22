#include "SkillHandler.h"



Skill::SkillHandler::SkillHandler()
{
}


Skill::SkillHandler::~SkillHandler()
{
	for each (Skill::SkillBase* skill in skillBox)
	{
		delete skill;
	}
	skillBox.clear();
}

void Skill::SkillHandler::runSkill(int index)
{
	skillBox[index]->active();
}

void Skill::SkillHandler::runSkill(const std::string& skillName)
{
	for each (SkillBase* skill in skillBox)
	{
		if (skill->getName() == skillName)
		{
			skill->active();
			return;
		}
	}
}

std::vector<Skill::SkillBase* >& Skill::SkillHandler::getSkillBoxRef()
{
	return skillBox;
}

void Skill::SkillHandler::addSkill(SkillBase* skill)
{
	skillBox.push_back(skill);
}
