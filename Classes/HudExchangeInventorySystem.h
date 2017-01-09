#pragma once

#include "Singleton.h"
#include "HudMenu.h"

class Character;

class HudExchangeInventoryMenu :public HudMenu
{
public:
	HudExchangeInventoryMenu();
	~HudExchangeInventoryMenu();
	void update();

	void setCharacter(Character* character);

protected:
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

	void AgiveB();

	void exchangeInventory(Character* A, Character* B);
protected:
	HudExchangeInventoryMenu* menuA;
	HudExchangeInventoryMenu* menuB;
	Character* characterA;
	Character* characterB;
};
