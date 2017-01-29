#include "HudEquipableInventoryMenu.h"
#include "HudDescriptionMenu.h"
#include "HudMenuItem.h"
#include "ToolFunction.h"
#include "HudTrigEquipLeft.h"
#include "HudTrigEquipRight.h"
#include "HudTrigDrop.h"
#include "HudLayout.h"
#include "HudTrigThrow.h"



HudEquipableInventoryMenu::HudEquipableInventoryMenu()
	:HudMenu(cocos2d::Rect(0,0,
		HudLayout::getInstance()->getLeafMenuSize().width,
		HudLayout::getInstance()->getLeafMenuSize().height))
{
	this->setPosition(HudLayout::getInstance()->getLeafMenuPosition().x,
		HudLayout::getInstance()->getLeafMenuPosition().y);

	HudMenuItem* equipLeftMenuItem = new HudMenuItem(ToolFunction::WStr2UTF8(L"装备左手"));
	HudTrigEquipLeft* equipLeftTrig = new HudTrigEquipLeft();
	equipLeftMenuItem->setTrigger(equipLeftTrig);
	this->addItem(equipLeftMenuItem);

	HudMenuItem* equipRightMenuItem = new HudMenuItem(ToolFunction::WStr2UTF8(L"装备右手"));
	HudTrigEquipRight* equipRightTrig = new HudTrigEquipRight();
	equipRightMenuItem->setTrigger(equipRightTrig);
	this->addItem(equipRightMenuItem);

	HudMenuItem* dropMenuItem = new HudMenuItem(ToolFunction::WStr2UTF8(L"丢弃"));
	HudTrigDrop* dropTrig = new HudTrigDrop();
	dropMenuItem->setTrigger(dropTrig);
	this->addItem(dropMenuItem);


//	HudMenuItem* throwMenuItem = new HudMenuItem(ToolFunction::WStr2UTF8(L"投掷"));
//	HudTrigThrow* throwTrig = new HudTrigThrow();
//	throwMenuItem->setTrigger(throwTrig);
//	this->addItem(throwMenuItem);

	hide();
}


HudEquipableInventoryMenu::~HudEquipableInventoryMenu()
{
}

void HudEquipableInventoryMenu::show()
{
	HudMenu::show();

	HudDescriptionMenu::getInstance()->hide();
}
