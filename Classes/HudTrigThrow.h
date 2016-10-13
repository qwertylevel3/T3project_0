#pragma once

#include "HudTrigger.h"
#include "base/ccTypes.h"


class Character;
class Inventory;


class HudTrigThrow:public HudTrigger
{
public:
	HudTrigThrow();
	~HudTrigThrow();
	void run();
protected:
	cocos2d::Point getTarget();
	void showEffect(Inventory* inventory,cocos2d::Point targetCoord);
	void throwResult(Inventory* inventory,cocos2d::Point targetCoord);
};

