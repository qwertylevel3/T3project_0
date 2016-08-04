#pragma once

#include"cocos2d.h"

class Inventory
{
public:
	Inventory();
	~Inventory();
protected:
	CC_SYNTHESIZE(int, id, Id);
	CC_SYNTHESIZE(std::string, name, Name);
	CC_SYNTHESIZE(int, price, Price);
	CC_SYNTHESIZE(int, weight, Weight);
	CC_SYNTHESIZE(cocos2d::Sprite*, sprite, Sprite);
};

