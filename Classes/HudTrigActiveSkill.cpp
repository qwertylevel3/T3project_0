#include "HudTrigActiveSkill.h"
#include "KeyController.h"
#include "HudSkillMenu.h"
#include "Player.h"
#include "SkillHandler.h"
#include "HudMenuItem.h"



HudTrigActiveSkill::HudTrigActiveSkill()
{
}


HudTrigActiveSkill::~HudTrigActiveSkill()
{
}

void HudTrigActiveSkill::run()
{
	int curIndex = HudSkillMenu::getInstance()->getCurIndex();
	Character* characterPtr = Player::getInstance()->getcharacterPtr();

	Skill::SkillHandler* skillHandler = characterPtr->getSkillHandler();
	std::string skillID = skillHandler->getSkillID(curIndex);
	characterPtr->runSkill(skillID);
	KeyController::getInstance()->switchCtrlToPlayer();

	menuItem->getParentMenu()->closeMenu();
}
