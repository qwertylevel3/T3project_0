#include "HudAccessoryMenu.h"
#include "HudDescriptionMenu.h"
#include "HudTrigDrop.h"
#include "HudTrigThrow.h"
#include "HudMenuItem.h"
#include "HudLayout.h"
#include "ToolFunction.h"
#include "HudTrigEquipAccessory.h"



HudAccessoryMenu::HudAccessoryMenu()
	:HudMenu(cocos2d::Rect(0,0,
		HudLayout::getInstance()->getLeafMenuSize().width,
		HudLayout::getInstance()->getLeafMenuSize().height))
{
	this->setPosition(HudLayout::getInstance()->getLeafMenuPosition().x,
		HudLayout::getInstance()->getLeafMenuPosition().y);


	HudMenuItem* equipMenuItem = new HudMenuItem(ToolFunction::WStr2UTF8(L"×°±¸"));
	HudTrigEquipAccessory* equipTrig = new HudTrigEquipAccessory();
	equipMenuItem->setTrigger(equipTrig);
	this->addItem(equipMenuItem);


	HudMenuItem* dropMenuItem = new HudMenuItem(ToolFunction::WStr2UTF8(L"¶ªÆú"));
	HudTrigDrop* dropTrig = new HudTrigDrop();
	dropMenuItem->setTrigger(dropTrig);
	this->addItem(dropMenuItem);


	HudMenuItem* throwMenuItem = new HudMenuItem(ToolFunction::WStr2UTF8(L"Í¶ÖÀ"));
	HudTrigThrow* throwTrig = new HudTrigThrow();
	throwMenuItem->setTrigger(throwTrig);
	this->addItem(throwMenuItem);

	hide();
}



HudAccessoryMenu::~HudAccessoryMenu()
{
}

void HudAccessoryMenu::show()
{
	HudMenu::show();

	HudDescriptionMenu::getInstance()->hide();
}
