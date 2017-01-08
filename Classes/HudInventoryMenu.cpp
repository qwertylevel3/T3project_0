#include "HudInventoryMenu.h"
#include "HudAccessoryMenu.h"
#include "HudArmorMenu.h"
#include "Player.h"
#include "Inventory.h"
#include "HudMenuItem.h"
#include "ToolFunction.h"
#include "InventoryHandler.h"
#include "InventoryFactory.h"
#include "ToolFunction.h"
#include "HudTrigActChildMenu.h"
#include "HudEquipableInventoryMenu.h"
#include "HudUseableInventoryMenu.h"
#include "HudLayer.h"
#include "HudLayout.h"
#include "HudDescriptionMenu.h"
#include "HudCursor.h"


HudInventoryMenu::HudInventoryMenu()
	:HudMenu(cocos2d::Rect(
		0,0,
		HudLayout::getInstance()->getMediumMenuSize().width,
		HudLayout::getInstance()->getMediumMenuSize().height))
{
	this->setPosition(HudLayout::getInstance()->getMediumMenuPosition().x,
		HudLayout::getInstance()->getMediumMenuPosition().y);
}


HudInventoryMenu::~HudInventoryMenu()
{
}

void HudInventoryMenu::show()
{
	HudMenu::show();
	HudDescriptionMenu::getInstance()->show();
}

void HudInventoryMenu::hide()
{
	HudMenu::hide();
	HudDescriptionMenu::getInstance()->hide();
}

void HudInventoryMenu::update()
{
	clear();
	InventoryHandler* inventoryHandler = Player::getInstance()->getcharacterPtr()->getInventoryHandler();
	//std::vector<Inventory*>& inventoryList = Player::getInstance()->getInventoryList();

	std::map<std::string, int> inventoryMap = inventoryHandler->getAllInventory();

	std::map<std::string, int>::const_iterator iter = inventoryMap.cbegin();
	while (iter != inventoryMap.cend())
	{
		std::string cname = InventoryFactory::getInstance()->queryCname(iter->first);
		std::string count = ToolFunction::int2string(iter->second);

		HudMenuItem* inventoryItem = new HudMenuItem(cname+" x"+count);

		setItemTrigger(iter->first,inventoryItem);
		this->addItem(inventoryItem);

		iter++;
	}
	if (itemList.empty())
	{
		HudMenuItem* emptyItem = new HudMenuItem("empty");
		this->addItem(emptyItem);
	}
	HudCursor::getInstance()->setCurMenu(this);
}

void HudInventoryMenu::init()
{

}

void HudInventoryMenu::addItem(HudMenuItem* item)
{
	HudMenu::addItem(item);
	item->setAliginment(cocos2d::TextHAlignment::LEFT);
}


void HudInventoryMenu::chooseItem(int index)
{
	HudMenu::chooseItem(index);

	InventoryHandler* inventoryHandler = Player::getInstance()->getcharacterPtr()->getInventoryHandler();
	std::map<std::string, int> inventoryMap = inventoryHandler->getAllInventory();

	std::map<std::string, int>::iterator iter = inventoryMap.begin();

	int count = 0;
	while (iter!=inventoryMap.end()
		&& count!=index)
	{
		count++;
		iter++;
	}
	if (iter==inventoryMap.end())
	{
		return;
	}

	std::string inventoryID = iter->first;

	Inventory* inventory = InventoryFactory::getInstance()->getInventory(inventoryID);


	HudDescriptionMenu::getInstance()->setDescription(
		inventory->getDescription()
	);
	delete inventory;
}

void HudInventoryMenu::setItemTrigger(const std::string& inventoryName, HudMenuItem* item)
{
	Inventory::Type inventoryType = InventoryFactory::getInstance()->queryInventoryType(inventoryName);
	switch (inventoryType)
	{
	case Inventory::Other:
		break;
	case Inventory::OneHandWeapon:
		initEquipableInventoryMenu(item);
		break;
	case Inventory::TwoHandWeapon:
	case Inventory::Shield:
	case Inventory::Armor:
		initArmorMenu(item);
		break;
	case Inventory::Bow:
		initEquipableInventoryMenu(item);
		break;
	case Inventory::Supply:
		initUseableInventoryMenu(item);
		break;
	case Inventory::Accessory:
		initAccessoryMenu(item);
		break;
	default:
		break;
	}
}

void HudInventoryMenu::initEquipableInventoryMenu(HudMenuItem* item)
{
	HudEquipableInventoryMenu* menu = new HudEquipableInventoryMenu();

	menu->setParent(this);

	HudTrigActChildMenu* trigger = new HudTrigActChildMenu(menu);
	item->setTrigger(trigger);
}

void HudInventoryMenu::initUseableInventoryMenu(HudMenuItem* item)
{
	HudUseableInventoryMenu* menu = new HudUseableInventoryMenu();

	menu->setParent(this);

	HudTrigActChildMenu* trigger = new HudTrigActChildMenu(menu);
	item->setTrigger(trigger);
}

void HudInventoryMenu::initArmorMenu(HudMenuItem* item)
{
	HudArmorMenu* menu = new HudArmorMenu();
	menu->setParent(this);

	HudTrigActChildMenu* trigger = new HudTrigActChildMenu(menu);
	item->setTrigger(trigger);
}

void HudInventoryMenu::initAccessoryMenu(HudMenuItem* item)
{
	HudAccessoryMenu* menu = new HudAccessoryMenu();

	menu->setParent(this);

	HudTrigActChildMenu* trigger = new HudTrigActChildMenu(menu);
	item->setTrigger(trigger);
}
