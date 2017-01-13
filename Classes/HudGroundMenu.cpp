#include "HudGroundMenu.h"
#include "InventoryFactory.h"
#include "HudCursor.h"
#include "HudLayout.h"
#include "HudMenuItem.h"
#include "base/ccTypes.h"
#include "Dungeon.h"
#include "StoreyInventoryHandler.h"
#include "Player.h"
#include "HudGroundInventoryMenu.h"
#include "Inventory.h"
#include "HudTrigActChildMenu.h"
#include "HudDescriptionMenu.h"



HudGroundMenu::HudGroundMenu()
	:HudMenu(cocos2d::Rect(0,0,
		HudLayout::getInstance()->getMediumMenuSize().width,
		HudLayout::getInstance()->getMediumMenuSize().height))
{
	this->setPosition(HudLayout::getInstance()->getMediumMenuPosition().x,
		HudLayout::getInstance()->getMediumMenuPosition().y);
}


HudGroundMenu::~HudGroundMenu()
{
}

void HudGroundMenu::addItem(HudMenuItem* item)
{
	HudMenu::addItem(item);
	item->setAliginment(cocos2d::TextHAlignment::LEFT);
}

void HudGroundMenu::update()
{
	clear();

	Field::Storey* storey = Field::Dungeon::getInstance()->getStorey();
	StoreyInventoryHandler* storeyInventoryHandler = storey->getInventoryHandler();
	Character* characterPrt = Player::getInstance()->getcharacterPtr();
	TileInventoryHandler* curInventoryHandler = 
		storeyInventoryHandler->getTileInventoryHandler(
			characterPrt->getMapCoord().x, 
			characterPrt->getMapCoord().y);

	std::vector<Inventory* > inventoryBox = curInventoryHandler->getInventoryBox();

	for each (Inventory* inventory in inventoryBox)
	{
		HudMenuItem* menuItem = new HudMenuItem(inventory->getCname());

		HudGroundInventoryMenu* inventoryMenu = new HudGroundInventoryMenu();
		inventoryMenu->setParent(this);
		HudTrigActChildMenu* trigger = new HudTrigActChildMenu(inventoryMenu);

		menuItem->setTrigger(trigger);

		this->addItem(menuItem);
	}

	if (itemList.empty())
	{
		HudMenuItem* emptyItem = new HudMenuItem("empty");
		HudDescriptionMenu::getInstance()->setDescription(L"empty");
		this->addItem(emptyItem);

	}
	HudCursor::getInstance()->setCurMenu(this);
}

void HudGroundMenu::chooseItem(int index)
{
	HudMenu::chooseItem(index);

	index = index > itemList.size() - 1 ? itemList.size()-1 : index;
	index = index < 0 ? 0 : index;


	Field::Storey* storey = Field::Dungeon::getInstance()->getStorey();
	StoreyInventoryHandler* storeyInventoryHandler = storey->getInventoryHandler();
	Character* characterPrt = Player::getInstance()->getcharacterPtr();
	TileInventoryHandler* curInventoryHandler = 
		storeyInventoryHandler->getTileInventoryHandler(
			characterPrt->getMapCoord().x, 
			characterPrt->getMapCoord().y);

	std::vector<Inventory* > inventoryBox = curInventoryHandler->getInventoryBox();

	index = index > inventoryBox.size() - 1 ? inventoryBox.size()-1 : index;

	if (inventoryBox.size()==0)
	{
		return;
	}

	Inventory* inventory = inventoryBox[index];

	HudDescriptionMenu::getInstance()->setDescription(
		inventory->getDescription()
	);
	if (layout->isVisible())
	{
		HudDescriptionMenu::getInstance()->show();
	}
}

void HudGroundMenu::show()
{
	HudMenu::show();
	HudDescriptionMenu::getInstance()->show();
}

void HudGroundMenu::hide()
{
	HudMenu::hide();
	HudDescriptionMenu::getInstance()->hide();
}

