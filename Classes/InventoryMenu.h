#pragma once

#include"cocos2d.h"
#include"Singleton.h"

class InventoryMenu:public Singleton<InventoryMenu>
{
public:
	void init();
	InventoryMenu();
	~InventoryMenu();
	void show();
	void hide();
protected:
	CC_SYNTHESIZE(cocos2d::Sprite*, sprite, Sprite);
};

