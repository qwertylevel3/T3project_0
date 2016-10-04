#pragma once

#include<vector>
#include "base/ccMacros.h"
#include "base/ccTypes.h"

class Inventory;
namespace cocos2d
{
	class Sprite;
}

class TileInventoryHandler
{
public:
	TileInventoryHandler();
	~TileInventoryHandler();
	void addInventory(Inventory* inventory);
	void removeInventory(int index);
	bool isEmpty();
protected:
	std::vector<Inventory*> inventoryBox;
	//用于显示在地图上的sprite
	cocos2d::Sprite* sprite;
	CC_SYNTHESIZE(cocos2d::Point, coord, Coord);
};

class StoreyInventoryHandler
{
public:
	StoreyInventoryHandler(int w,int h);
	~StoreyInventoryHandler();
	void addInventory(Inventory* inventory, int x, int y);
	void removeInventory(int index, int x, int y);
	TileInventoryHandler* getTileInventoryHandler(int x,int y);
protected:
	std::vector<TileInventoryHandler*> handlerMap;
	int width;
	int height;
};

