#include "HudUnequipArmorMenu.h"
#include "ToolFunction.h"
#include "HudTrigUnequipArmor.h"
#include "HudLayout.h"
#include "HudMenuItem.h"



HudUnequipArmorMenu::HudUnequipArmorMenu()
	:HudMenu(cocos2d::Rect(0,0,
		HudLayout::getInstance()->getLeafMenuSize().width,
		HudLayout::getInstance()->getLeafMenuSize().height))
{
	this->setPosition(HudLayout::getInstance()->getLeafMenuPosition().x,
		HudLayout::getInstance()->getLeafMenuPosition().y);


	HudMenuItem* menuItem = new HudMenuItem(ToolFunction::WStr2UTF8(L"п╤об"));

	HudTrigUnequipArmor* trigger = new HudTrigUnequipArmor();
	
	menuItem->setTrigger(trigger);
	this->addItem(menuItem);
}




HudUnequipArmorMenu::~HudUnequipArmorMenu()
{
}
