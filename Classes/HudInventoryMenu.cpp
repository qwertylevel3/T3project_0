#include "HudInventoryMenu.h"
#include "Player.h"
#include "Inventory.h"
#include "HudMenuItem.h"
#include "ToolFunction.h"
#include "InventoryHandler.h"
#include "InventoryManager.h"
#include "ToolFunction.h"
#include "HudTrigActChildMenu.h"
#include "HudEquipableInventoryMenu.h"
#include "HudLayer.h"
#include "HudLayout.h"


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

void HudInventoryMenu::update()
{
	clear();
	InventoryHandler* inventoryHandler = Player::getInstance()->getcharacterPtr()->getInventoryHandler();
	//std::vector<Inventory*>& inventoryList = Player::getInstance()->getInventoryList();

	std::map<std::string, int> inventoryMap = inventoryHandler->getAllInventory();

	std::map<std::string, int>::const_iterator iter = inventoryMap.cbegin();
	while (iter != inventoryMap.cend())
	{
		std::string cname = InventoryManager::getInstance()->getCname(iter->first);
		std::string count = ToolFunction::int2string(iter->second);

		HudMenuItem* inventoryItem = new HudMenuItem(cname+" x"+count);

		setItemTrigger(iter->first,inventoryItem);
		this->addItem(inventoryItem);

		iter++;
	}
}

void HudInventoryMenu::init()
{

}

void HudInventoryMenu::addItem(HudMenuItem* item)
{
	HudMenu::addItem(item);
	item->setAliginment(cocos2d::TextHAlignment::LEFT);
}

void HudInventoryMenu::setItemTrigger(const std::string& inventoryName,HudMenuItem* item)
{
	Inventory::Type inventoryType = InventoryManager::getInstance()->getInventoryType(inventoryName);
	switch (inventoryType)
	{
	case Inventory::Empty:
		break;
	case Inventory::OneHandWeapon:
	case Inventory::TwoHandWeapon:
	case Inventory::Shield:
	case Inventory::Armor:
		initEquipableInventoryMenu(item);
		break;
	case Inventory::Supply:
		break;
	case Inventory::Accessory:
		break;
	case Inventory::Other:
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
