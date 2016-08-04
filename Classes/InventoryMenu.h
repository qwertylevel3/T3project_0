#pragma once

#include"cocos2d.h"
#include"Singleton.h"

class InventoryMenuItem;

class InventoryMenu:public Singleton<InventoryMenu>
{
public:
	void init();
	InventoryMenu();
	~InventoryMenu();
	void show();
	void hide();
	void addItem(InventoryMenuItem* item,int index);
protected:
	CC_SYNTHESIZE(cocos2d::Sprite*, sprite, Sprite);
};

