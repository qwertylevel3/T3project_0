#pragma once

#include"cocos2d.h"

class Character;

class Inventory
{

public:
	enum Type
	{
		Weapon, Armor, Supply, Accessory
	};

	Inventory();
	~Inventory();
	virtual void equip(Character* character);
	virtual void unequip(Character* character);
	virtual void load(Character* character);
	virtual void unload(Character* character);
	virtual void use(Character* character);
protected:
	CC_SYNTHESIZE(int, id, Id);
	CC_SYNTHESIZE(std::string, name, Name);
	CC_SYNTHESIZE(std::wstring, cname, Cname);
	CC_SYNTHESIZE(int, price, Price);
	CC_SYNTHESIZE(int, weight, Weight);
	CC_SYNTHESIZE(cocos2d::Sprite*, icon, Icon);
	CC_SYNTHESIZE(Inventory::Type, inventoryType, InventoryType);
};

