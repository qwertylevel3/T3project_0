#include "HudInventoryMenu.h"
#include "Player.h"
#include "Inventory.h"
#include "HudMenuItem.h"
#include "ToolFunction.h"
#include "InventoryHandler.h"
#include "InventoryManager.h"
#include "ToolFunction.h"



HudInventoryMenu::HudInventoryMenu(cocos2d::Rect rect)
	:HudMenu(rect)
{
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
		this->addItem(inventoryItem);

		iter++;
	}
}

void HudInventoryMenu::addItem(HudMenuItem* item)
{
	HudMenu::addItem(item);
	item->setAliginment(cocos2d::TextHAlignment::LEFT);
}
