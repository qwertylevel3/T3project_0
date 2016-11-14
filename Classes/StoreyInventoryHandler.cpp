#include "StoreyInventoryHandler.h"
#include "2d/CCSprite.h"
#include "MainLayer.h"
#include "Dungeon.h"


TileInventoryHandler::TileInventoryHandler()
{

}

TileInventoryHandler::~TileInventoryHandler()
{
	MainLayer::getInstance()->removeChild(sprite);
	std::vector<Inventory*>::iterator iter = inventoryBox.begin();
	while (iter != inventoryBox.end())
	{
		delete *iter;
		iter++;
	}
}

void TileInventoryHandler::addInventory(Inventory* inventory)
{
	if (isEmpty())
	{
		sprite = cocos2d::Sprite::create("inventory.png");
		Field::Storey* storey = Field::Dungeon::getInstance()->getStorey();
		int storeyHeight = storey->getHeight();
		sprite->setPosition(cocos2d::Point(coord.x * 32 + 16, (storeyHeight - coord.y) * 32 - 16));
		MainLayer::getInstance()->addChild(sprite, 5);
	}
	inventoryBox.push_back(inventory);
}

void TileInventoryHandler::removeInventory(int index)
{
	int count = 0;
	std::vector<Inventory*>::iterator iter = inventoryBox.begin();
	while (iter != inventoryBox.end())
	{
		if (count == index)
		{
			inventoryBox.erase(iter);
			if (inventoryBox.empty())
			{
				MainLayer::getInstance()->removeChild(sprite);
			}
			return;
		}
		index++;
		iter++;
	}
}

bool TileInventoryHandler::isEmpty()
{
	return inventoryBox.empty();
}

Inventory* TileInventoryHandler::getInventory(int index)
{
	int count = 0;
	std::vector<Inventory*>::iterator iter = inventoryBox.begin();
	while (iter != inventoryBox.end())
	{
		if (count == index)
		{
			Inventory* inventory = *iter;
			return inventory;
		}
		count++;
		iter++;
	}
	return nullptr;
}

std::vector<Inventory*>& TileInventoryHandler::getInventoryBox()
{
	return inventoryBox;
}

//////////////////////////////////////////////////////////////////////////

StoreyInventoryHandler::StoreyInventoryHandler(int w,int h)
{
	width = w;
	height = h;
	for (int i = 0; i < w; i++)
	{
		for (int j = 0; j < h; j++)
		{
			TileInventoryHandler* handler = new TileInventoryHandler();
			handler->setCoord(cocos2d::Point(j, i));

			handlerMap.push_back(handler);
		}
	}

}


StoreyInventoryHandler::~StoreyInventoryHandler()
{
}

void StoreyInventoryHandler::addInventory(Inventory* inventory, int x, int y)
{
	handlerMap[x + y*width]->addInventory(inventory);
}

void StoreyInventoryHandler::removeInventory(int index, int x, int y)
{
	handlerMap[x + y*width]->removeInventory(index);
}

Inventory* StoreyInventoryHandler::getInventory(int index, int x, int y)
{
	return handlerMap[x + width*y]->getInventory(index);
}

TileInventoryHandler* StoreyInventoryHandler::getTileInventoryHandler(int x, int y)
{
	return handlerMap[x + y*width];
}

