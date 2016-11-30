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

bool Skill::SkillHandler::runSkill(int index)
{
	return skillBox[index]->active();
}

bool Skill::SkillHandler::runSkill(const std::string& skillName)
{
	for each (SkillBase* skill in skillBox)
	{
		if (skill->getName() == skillName)
		{
			return skill->active();
		}
	}
	return false;
}

std::vector<Skill::SkillBase* >& Skill::SkillHandler::getSkillBoxRef()
{
	return skillBox;
}

void Skill::SkillHandler::addSkill(SkillBase* skill)
{
	skillBox.push_back(skill);
}

std::string Skill::SkillHandler::getSkillName(int index)
{
	return skillBox[index]->getName();
}
