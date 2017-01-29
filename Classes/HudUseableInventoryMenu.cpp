#include "HudUseableInventoryMenu.h"
#include "HudDescriptionMenu.h"
#include "HudLayout.h"
#include "HudTrigUseInventory.h"
#include "HudTrigDrop.h"
#include "HudTrigThrow.h"
#include "HudMenuItem.h"
#include "ToolFunction.h"



HudUseableInventoryMenu::HudUseableInventoryMenu()
	:HudMenu(cocos2d::Rect(0,0,
		HudLayout::getInstance()->getLeafMenuSize().width,
		HudLayout::getInstance()->getLeafMenuSize().height))
{
	this->setPosition(HudLayout::getInstance()->getLeafMenuPosition().x,
		HudLayout::getInstance()->getLeafMenuPosition().y);

	HudMenuItem* useMenuItem = new HudMenuItem(ToolFunction::WStr2UTF8(L"Ê¹ÓÃ"));
	HudTrigUseInventory* useTrig = new HudTrigUseInventory();
	useMenuItem->setTrigger(useTrig);
	this->addItem(useMenuItem);

	HudMenuItem* dropMenuItem = new HudMenuItem(ToolFunction::WStr2UTF8(L"¶ªÆú"));
	HudTrigDrop* dropTrig = new HudTrigDrop();
	dropMenuItem->setTrigger(dropTrig);
	this->addItem(dropMenuItem);


//	HudMenuItem* throwMenuItem = new HudMenuItem(ToolFunction::WStr2UTF8(L"Í¶ÖÀ"));
//	HudTrigThrow* throwTrig = new HudTrigThrow();
//	throwMenuItem->setTrigger(throwTrig);
//	this->addItem(throwMenuItem);

	hide();
}


HudUseableInventoryMenu::~HudUseableInventoryMenu()
{
}

void HudUseableInventoryMenu::show()
{
	HudMenu::show();

	HudDescriptionMenu::getInstance()->hide();
}
