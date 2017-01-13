#pragma once

#include "Singleton.h"
#include "HudMenu.h"

#include "2d/CCLabel.h"


class Character;

class HudExchangeInventoryMenu :public HudMenu
{
public:
	HudExchangeInventoryMenu();
	~HudExchangeInventoryMenu();
	void update();
	void handleLeft();
	void handleRight();

	void setCharacter(Character* character);

protected:
	cocos2d::Label* titleLabel;
	Character* characterPtr;
	void setItemTrigger(HudMenuItem* item);
};

class HudExchangeInventorySystem :public Singleton<HudExchangeInventorySystem>
{
public:
	HudExchangeInventorySystem();
	~HudExchangeInventorySystem();
	void init();
	void close();

	void give();

	void AgiveB();
	void BgiveA();

	void changeGive();

	void exchangeInventory(Character* A, Character* B);
protected:

	void showArrow();
	
	HudExchangeInventoryMenu* menuA;
	HudExchangeInventoryMenu* menuB;
	Character* characterA;
	Character* characterB;

	cocos2d::Sprite* leftArrow;
	cocos2d::Sprite* rightArrow;

	//true:A->B
	//false:B->A
	bool curGive;
};
