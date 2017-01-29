#include "HudArmorMenu.h"
#include "HudDescriptionMenu.h"
#include "HudTrigEquipArmor.h"
#include "HudTrigThrow.h"
#include "HudTrigDrop.h"
#include "ToolFunction.h"
#include "HudMenuItem.h"
#include "HudLayout.h"




HudArmorMenu::HudArmorMenu()
	:HudMenu(cocos2d::Rect(0,0,
		HudLayout::getInstance()->getLeafMenuSize().width,
		HudLayout::getInstance()->getLeafMenuSize().height))
{
	this->setPosition(HudLayout::getInstance()->getLeafMenuPosition().x,
		HudLayout::getInstance()->getLeafMenuPosition().y);


	HudMenuItem* equipMenuItem = new HudMenuItem(ToolFunction::WStr2UTF8(L"×°±¸"));
	HudTrigEquipArmor* equipTrig = new HudTrigEquipArmor();
	equipMenuItem->setTrigger(equipTrig);
	this->addItem(equipMenuItem);

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


HudArmorMenu::~HudArmorMenu()
{
}

void HudArmorMenu::show()
{
	HudMenu::show();

	HudDescriptionMenu::getInstance()->hide();
}
