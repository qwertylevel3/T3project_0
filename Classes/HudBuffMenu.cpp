#include "HudBuffMenu.h"
#include "HudLayout.h"
#include "HudMenuItem.h"



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


	//todo

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
