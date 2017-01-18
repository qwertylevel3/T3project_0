#include "HudSkillMenu.h"
#include "ToolFunction.h"
#include "HudLayout.h"
#include "HudMenuItem.h"
#include "Player.h"
#include "SkillHandler.h"
#include "SkillBase.h"
#include "HudTrigActiveSkill.h"
#include "HudDescriptionMenu.h"



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

	int count = 1;
	for each (Skill::SkillBase* skill in skillBox)
	{
		HudMenuItem* item = new HudMenuItem(
			ToolFunction::int2string(count++)+
			":"+
			skill->getCname()
		);
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

void HudSkillMenu::show()
{
	HudMenu::show();
	HudDescriptionMenu::getInstance()->show();
}

void HudSkillMenu::hide()
{
	HudMenu::hide();
	HudDescriptionMenu::getInstance()->hide();
}

void HudSkillMenu::chooseItem(int index)
{
	HudMenu::chooseItem(index);
	Character* characterPrt = Player::getInstance()->getcharacterPtr();
	Skill::SkillHandler* skillHandler = characterPrt->getSkillHandler();

	std::vector<Skill::SkillBase*> skillBox = skillHandler->getSkillBoxRef();

	if (skillBox.empty())
	{
		return;
	}

	HudDescriptionMenu::getInstance()->setDescription(
		skillBox[index]->getDescription()
	);
}
