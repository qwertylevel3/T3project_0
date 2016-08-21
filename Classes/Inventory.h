#pragma once

#include"cocos2d.h"

class Character;

class Inventory
{

public:
	enum Type
	{
		Weapon, Armor, Supply, Accessory,Other
	};

	Inventory();
	virtual ~Inventory()=0;
	virtual Inventory* clone()=0;
	virtual void equipLeftHand(Character* character);
	virtual void unequipLeftHand(Character* character);
	virtual void equipRightHand(Character* character);
	virtual void unequipRightHand(Character* character);
	virtual void load(Character* character);
	virtual void unload(Character* character);
	virtual void use(Character* character);
	void copyData(Inventory* inventory);
	cocos2d::Sprite* getIcon();

protected:
	CC_SYNTHESIZE(int, id, Id);
	CC_SYNTHESIZE(std::string, name, Name);
	CC_SYNTHESIZE(std::wstring, cname, Cname);
	CC_SYNTHESIZE(int, price, Price);
	CC_SYNTHESIZE(int, weight, Weight);
	CC_SYNTHESIZE(std::string, spriteName, SpriteName);
	CC_SYNTHESIZE(Inventory::Type, inventoryType, InventoryType);

	cocos2d::Sprite* icon;

	CC_SYNTHESIZE(int, evadeProAdd, EvadeProAdd);
	CC_SYNTHESIZE(int, accuracyProAdd, AccuracyProAdd);
	CC_SYNTHESIZE(int, criticalProAdd, CriticalProAdd);
	CC_SYNTHESIZE(int, criticalAdd, CriticalAdd);
	CC_SYNTHESIZE(int, blockProAdd, BlockProAdd);
	CC_SYNTHESIZE(int, blockAdd, BlockAdd);
	CC_SYNTHESIZE(int, comboProAdd, ComboProAdd);
};

