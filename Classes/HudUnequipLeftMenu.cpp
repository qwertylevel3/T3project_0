#include "HudUnequipLeftMenu.h"
#include "HudLayout.h"
#include "HudMenuItem.h"
#include "ToolFunction.h"
#include "HudTrigUnequipLeft.h"



HudUnequipLeftMenu::HudUnequipLeftMenu()
	:HudMenu(cocos2d::Rect(0,0,
		HudLayout::getInstance()->getLeafMenuSize().width,
		HudLayout::getInstance()->getLeafMenuSize().height))
{
	this->setPosition(HudLayout::getInstance()->getLeafMenuPosition().x,
		HudLayout::getInstance()->getLeafMenuPosition().y);


	HudMenuItem* menuItem = new HudMenuItem(ToolFunction::WStr2UTF8(L"п╤об"));

	HudTrigUnequipLeft* trigger = new HudTrigUnequipLeft();
	menuItem->setTrigger(trigger);
	this->addItem(menuItem);
}


HudUnequipLeftMenu::~HudUnequipLeftMenu()
{
}
