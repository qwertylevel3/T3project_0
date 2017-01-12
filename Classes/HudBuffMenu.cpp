#include "HudBuffMenu.h"
#include "HudCursor.h"
#include "HudLayout.h"
#include "HudMenuItem.h"
#include "Player.h"
#include "BuffHandler.h"
#include "BuffBase.h"
#include "HudDescriptionMenu.h"
#include "ToolFunction.h"



HudBuffMenu::HudBuffMenu()
	:HudMenu(cocos2d::Rect(
		0,0,
		HudLayout::getInstance()->getMediumMenuSize().width,
		HudLayout::getInstance()->getMediumMenuSize().height))
{
	this->setPosition(HudLayout::getInstance()->getMediumMenuPosition().x,
		HudLayout::getInstance()->getMediumMenuPosition().y);
}


HudBuffMenu::~HudBuffMenu()
{
}

void HudBuffMenu::show()
{
	HudMenu::show();
	HudDescriptionMenu::getInstance()->show();
}

void HudBuffMenu::hide()
{
	HudMenu::hide();
	HudDescriptionMenu::getInstance()->hide();
}

void HudBuffMenu::update()
{
	clear();
	//////////////////////////////////////////////////////////////////////////
	Character* characterPrt = Player::getInstance()->getcharacterPtr();
	Buff::BuffHandler* buffHandler = characterPrt->getBuffHandler();

	std::vector<Buff::BuffBase* > buffBox = buffHandler->getBuffBoxRef();

	for each (Buff::BuffBase* buff in buffBox)
	{
		HudMenuItem* menuItem = new HudMenuItem(buff->getCname());
		this->addItem(menuItem);
	}

	//////////////////////////////////////////////////////////////////////////
	if (itemList.empty())
	{
		HudMenuItem* emptyItem = new HudMenuItem("empty");
		this->addItem(emptyItem);
	}
	HudCursor::getInstance()->setCurMenu(this);
	
}


void HudBuffMenu::chooseItem(int index)
{
	HudMenu::chooseItem(index);


	index = index > itemList.size() - 1 ? itemList.size()-1 : index;
	index = index < 0 ? 0 : index;



	Character* characterPrt = Player::getInstance()->getcharacterPtr();
	Buff::BuffHandler* buffHandler = characterPrt->getBuffHandler();

	std::vector<Buff::BuffBase* > buffBox = buffHandler->getBuffBoxRef();

	if (buffBox.empty())
	{
		return;
	}


	Buff::BuffBase* curBuff = buffBox[index];

	HudDescriptionMenu::getInstance()->setDescription(
		curBuff->getDurationDescriptionStr()+curBuff->getDescription()
	);
}

void HudBuffMenu::addItem(HudMenuItem* item)
{
	HudMenu::addItem(item);
	item->setAliginment(cocos2d::TextHAlignment::LEFT);
}
