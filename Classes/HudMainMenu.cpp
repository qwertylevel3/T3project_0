#include "HudMainMenu.h"
#include "HudLayout.h"
#include "base/ccTypes.h"
#include "HudMenuItem.h"
#include "ToolFunction.h"
#include "HudInventoryMenu.h"
#include "HudEquipMenu.h"
#include "HudTrigActChildMenu.h"
#include "HudGroundMenu.h"
#include "HudBuffMenu.h"
#include "HudSkillMenu.h"



HudMainMenu::HudMainMenu()
	:HudMenu(cocos2d::Rect(
		0,0,
		HudLayout::getInstance()->getmainMenuSize().width,
		HudLayout::getInstance()->getmainMenuSize().height))
{
	this->setPosition(HudLayout::getInstance()->getMainMenuPosition().x,
		HudLayout::getInstance()->getMainMenuPosition().y);
}


HudMainMenu::~HudMainMenu()
{
}

void HudMainMenu::init()
{
	HudInventoryMenu::getInstance()->init();
	HudEquipMenu::getInstance()->init();
	//////////////////////////////////////////////////////////////////////////

	HudMenuItem* buffMenuItem = new HudMenuItem(ToolFunction::WStr2UTF8(L"BUFF"));
	this->addItem(buffMenuItem);

	HudBuffMenu::getInstance()->setParent(this);

	HudTrigActChildMenu* buffTrigger = new HudTrigActChildMenu(HudBuffMenu::getInstance());
	buffMenuItem->setTrigger(buffTrigger);
	//////////////////////////////////////////////////////////////////////////

	HudMenuItem* skillMenuItem = new HudMenuItem(ToolFunction::WStr2UTF8(L"技能"));
	this->addItem(skillMenuItem);

	HudSkillMenu::getInstance()->setParent(this);

	HudTrigActChildMenu* skillTrigger = new HudTrigActChildMenu(HudSkillMenu::getInstance());
	skillMenuItem->setTrigger(skillTrigger);

	//////////////////////////////////////////////////////////////////////////

	HudMenuItem* inventoryMenuItem = new HudMenuItem(ToolFunction::WStr2UTF8(L"物品"));
	this->addItem(inventoryMenuItem);

	HudInventoryMenu::getInstance()->setParent(this);

	HudTrigActChildMenu* inventoryTrigger = new HudTrigActChildMenu(HudInventoryMenu::getInstance());
	inventoryMenuItem->setTrigger(inventoryTrigger);

	//////////////////////////////////////////////////////////////////////////

	HudMenuItem* equipMenuItem = new HudMenuItem(ToolFunction::WStr2UTF8(L"装备"));
	this->addItem(equipMenuItem);

	HudEquipMenu::getInstance()->setParent(this);

	HudTrigActChildMenu* equipTrigger = new HudTrigActChildMenu(HudEquipMenu::getInstance());
	equipMenuItem->setTrigger(equipTrigger);

	//////////////////////////////////////////////////////////////////////////

	HudMenuItem* groundMenuItem = new HudMenuItem(ToolFunction::WStr2UTF8(L"地面"));
	this->addItem(groundMenuItem);

	HudGroundMenu::getInstance()->setParent(this);

	HudTrigActChildMenu* groundTrigger = new HudTrigActChildMenu(HudGroundMenu::getInstance());
	groundMenuItem->setTrigger(groundTrigger);

}
