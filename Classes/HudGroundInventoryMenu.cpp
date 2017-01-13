#include "HudGroundInventoryMenu.h"
#include "HudDescriptionMenu.h"
#include "HudLayout.h"
#include "HudMenuItem.h"
#include "ToolFunction.h"
#include "HudTrigPick.h"



HudGroundInventoryMenu::HudGroundInventoryMenu()
	:HudMenu(cocos2d::Rect(0,0,
		HudLayout::getInstance()->getLeafMenuSize().width,
		HudLayout::getInstance()->getLeafMenuSize().height))
{
	this->setPosition(HudLayout::getInstance()->getLeafMenuPosition().x,
		HudLayout::getInstance()->getLeafMenuPosition().y);

	HudMenuItem* menuItem = new HudMenuItem(ToolFunction::WStr2UTF8(L"¼ñÆğ"));

	HudTrigPick* trigger = new HudTrigPick();
	menuItem->setTrigger(trigger);
	this->addItem(menuItem);
}


HudGroundInventoryMenu::~HudGroundInventoryMenu()
{
}

void HudGroundInventoryMenu::show()
{
	HudMenu::show();
	HudDescriptionMenu::getInstance()->hide();
}
