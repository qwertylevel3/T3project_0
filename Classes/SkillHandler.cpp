#include "SkillHandler.h"
#include "SkillFactory.h"



Skill::SkillHandler::SkillHandler(Character* character)
	:characterPtr(character)
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
	//TODO:refactor

	for each (SkillBase* skill in skillBox)
	{
		if (skill->getID() == skillName)
		{
			return skill->active();
		}
	}
	
	Skill::SkillBase* skill = Skill::SkillFactory::getInstance()->getSkill(characterPtr, skillName);

	bool isSuccess = skill->active();
	delete skill;
	return isSuccess;
}

std::vector<Skill::SkillBase* >& Skill::SkillHandler::getSkillBoxRef()
{
	return skillBox;
}

void Skill::SkillHandler::addSkill(SkillBase* skill)
{
	skillBox.push_back(skill);
}

std::string Skill::SkillHandler::getSkillID(int index)
{
	if (index>=skillBox.size())
	{
		return "";
	}
	return skillBox[index]->getID();
}
