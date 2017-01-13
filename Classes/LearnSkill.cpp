#include "LearnSkill.h"
#include "HudMessageBox.h"
#include "ToolFunction.h"
#include "SkillFactory.h"
#include "Character.h"

Skill::LearnSkill::LearnSkill()
{
}

Skill::LearnSkill::~LearnSkill()
{
}

Skill::LearnSkill* Skill::LearnSkill::createPrototype()
{
	return new Skill::LearnSkill();
}

void Skill::LearnSkill::run()
{
	caster->addSkill(
		skillID
	);

	std::string casterName = caster->getName();
	std::string skillName = SkillFactory::getInstance()->querySkillCname(skillID);

	HudMessageBox::getInstance()->addMessage(
		casterName +
		ToolFunction::WStr2UTF8(L"学习了") +
		skillName
	);
}

void Skill::LearnSkill::initExtraMessage(std::vector<std::string> extraMessage)
{
	skillID = extraMessage[0];

	for (int i=1;i<extraMessage.size();i++)
	{
		skillID += "_" + extraMessage[i];
	}
}

std::string Skill::LearnSkill::getExtraDescription()
{
	std::string skillName = SkillFactory::getInstance()->querySkillCname(skillID);

	return ToolFunction::WStr2UTF8(L"效果:\n") +
		ToolFunction::WStr2UTF8(L"学习技能:") + skillName;
}