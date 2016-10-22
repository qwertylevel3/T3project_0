#include "HudSkillMenu.h"
#include "HudLayout.h"
#include "HudMenuItem.h"
#include "Player.h"
#include "SkillHandler.h"
#include "SkillBase.h"
#include "HudTrigActiveSkill.h"



HudSkillMenu::HudSkillMenu()
	:HudMenu(cocos2d::Rect(
		0,0,
		HudLayout::getInstance()->getMediumMenuSize().width,
		HudLayout::getInstance()->getMediumMenuSize().height))
{
	this->setPosition(HudLayout::getInstance()->getMediumMenuPosition().x,
		HudLayout::getInstance()->getMediumMenuPosition().y);
}

HudSkillMenu::~HudSkillMenu()
{
}

void HudSkillMenu::update()
{
	clear();
	//////////////////////////////////////////////////////////////////////////

	Character* characterPrt = Player::getInstance()->getcharacterPtr();
	Skill::SkillHandler* skillHandler = characterPrt->getSkillHandler();

	std::vector<Skill::SkillBase*> skillBox = skillHandler->getSkillBoxRef();

	for each (Skill::SkillBase* skill in skillBox)
	{
		HudMenuItem* item = new HudMenuItem(skill->getCname());
		this->addItem(item);
		HudTrigActiveSkill* trigger = new HudTrigActiveSkill();
		item->setTrigger(trigger);
	}

	//////////////////////////////////////////////////////////////////////////
	if (itemList.empty())
	{
		HudMenuItem* emptyItem = new HudMenuItem("empty");
		this->addItem(emptyItem);
	}
}

void HudSkillMenu::addItem(HudMenuItem* item)
{
	HudMenu::addItem(item);
	item->setAliginment(cocos2d::TextHAlignment::LEFT);
}
