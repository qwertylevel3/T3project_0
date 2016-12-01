#include "SkillBase.h"
#include "SelectorBase.h"
#include "base/ccTypes.h"
#include <vector>
#include "HudMessageBox.h"
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
