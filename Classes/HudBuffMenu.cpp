#include "HudBuffMenu.h"
#include "HudLayout.h"
#include "HudMenuItem.h"
#include "Player.h"
#include "BuffHandler.h"
#include "BuffBase.h"



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

void HudBuffMenu::update()
{
	clear();
	//////////////////////////////////////////////////////////////////////////
	Character* characterPrt = Player::getInstance()->getcharacterPtr();
	BuffHandler* buffHandler = characterPrt->getBuffHandler();

	std::vector<BuffBase* > buffBox = buffHandler->getBuffBoxRef();

	for each (BuffBase* buff in buffBox)
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
}


void HudBuffMenu::addItem(HudMenuItem* item)
{
	HudMenu::addItem(item);
	item->setAliginment(cocos2d::TextHAlignment::LEFT);
}
