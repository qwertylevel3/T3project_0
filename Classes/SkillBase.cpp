#include "SkillBase.h"
#include "SelectorBase.h"
#include "base/ccTypes.h"
#include <vector>
#include "HudMessageBox.h"
#include "ToolFunction.h"
#include "Character.h"

using namespace Skill;

SkillBase::SkillBase(Character* character)
{
	caster = character;
	mpCost = 0;
	chantCost = 0;
}

SkillBase::~SkillBase()
{
}

bool Skill::SkillBase::active()
{
	if (!cost())
	{
		return false;
	}

	this->run();

	return true;
}

void Skill::SkillBase::init(std::vector<std::string> skillMessage)
{
	std::vector<std::string> baseMessage;
	std::vector<std::string > extraMessage;

	int i;
	for (i = 0; i < 3; i++)
	{
		baseMessage.push_back(skillMessage[i]);
	}
	for (; i < skillMessage.size(); i++)
	{
		extraMessage.push_back(skillMessage[i]);
	}
	initBaseMessage(baseMessage);
	this->initExtraMessage(extraMessage);
}

void Skill::SkillBase::initBaseMessage(std::vector<std::string> baseMessage)
{
	initCName(baseMessage[0]);
	initMPCost(baseMessage[1]);
	initChantCost(baseMessage[2]);
}


void Skill::SkillBase::initCName(std::string cn)
{
	cname = cn;
}

void Skill::SkillBase::initChantCost(std::string chantCostStr)
{
	chantCost = ToolFunction::string2int(chantCostStr);
}

void Skill::SkillBase::initMPCost(std::string MPCostStr)
{
	mpCost = ToolFunction::string2int(MPCostStr);
}

bool Skill::SkillBase::cost()
{
	if (chantCost > caster->getChant())
	{
		HudMessageBox::getInstance()->addMessage(L"吟唱点数不够");
		return false;
	}
	if (mpCost > caster->getMP())
	{
		HudMessageBox::getInstance()->addMessage(L"法力值不够");
		return false;
	}
	if (chantCost > 0)
	{
		caster->clearChant();
	}
	caster->sufferMPEffect(-mpCost);

	return true;
}

void Skill::SkillBase::run()
{
}