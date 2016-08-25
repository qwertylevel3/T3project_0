#include "HudInventoryMenu.h"
#include "Player.h"
#include "Inventory.h"
#include "HudMenuItem.h"
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
	std::vector<Inventory*>& inventoryList = Player::getInstance()->getInventoryList();
	for (size_t i=0;i<inventoryList.size();i++)
	{
		std::string cname = inventoryList[i]->getCname();
		HudMenuItem* inventoryItem = new HudMenuItem(cname);
		this->addItem(inventoryItem);
	}
}
