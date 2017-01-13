#include "HudUnequipAccessoryMenu.h"
#include "HudDescriptionMenu.h"
#include "ToolFunction.h"
#include "HudTrigUnequipAccessory.h"
#include "HudLayout.h"
#include "HudMenuItem.h"



HudUnequipAccessoryMenu::HudUnequipAccessoryMenu()
	:HudMenu(cocos2d::Rect(0,0,
		HudLayout::getInstance()->getLeafMenuSize().width,
		HudLayout::getInstance()->getLeafMenuSize().height))
{
	this->setPosition(HudLayout::getInstance()->getLeafMenuPosition().x,
		HudLayout::getInstance()->getLeafMenuPosition().y);


	HudMenuItem* menuItem = new HudMenuItem(ToolFunction::WStr2UTF8(L"Ğ¶ÏÂ"));

	HudTrigUnequipAccessory* trigger = new HudTrigUnequipAccessory();
	
	menuItem->setTrigger(trigger);
	this->addItem(menuItem);
}





HudUnequipAccessoryMenu::~HudUnequipAccessoryMenu()
{
}

void HudUnequipAccessoryMenu::show()
{
	HudMenu::show();
	HudDescriptionMenu::getInstance()->hide();
}
