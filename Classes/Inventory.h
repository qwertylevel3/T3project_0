#pragma once

#include"cocos2d.h"

class Character;
class InventoryBuffHandler;

class Inventory
{

public:
	enum Type
	{
		Empty,
		OneHandWeapon,TwoHandWeapon,Bow,Shield,Arrow, 
		Armor, Supply, Accessory, Other
	};

	Inventory();
	virtual ~Inventory() = 0;
	virtual Inventory* clone() = 0;
	virtual void equipLeftHand(Character* character);
	virtual void unequipLeftHand(Character* character);
	virtual void equipRightHand(Character* character);
	virtual void unequipRightHand(Character* character);
	virtual void equipArmor(Character* character);
	virtual void equipAccessory(Character* character);
	virtual void load(Character* character);
	virtual void unload(Character* character);
	virtual void use(Character* character);
	virtual void copyData(Inventory* inventory);
	cocos2d::Sprite* getIcon();

	void addBuff(std::string buffID);
	std::vector<std::string> getAllInventoryBuff();
protected:
	CC_SYNTHESIZE(int, id, Id);
	CC_SYNTHESIZE(std::string, name, Name);
	CC_SYNTHESIZE(std::string, cname, Cname);
	CC_SYNTHESIZE(int, price, Price);
	CC_SYNTHESIZE(int, weight, Weight);
	CC_SYNTHESIZE(int, level, Level);
	CC_SYNTHESIZE(std::string, spriteName, SpriteName);
	CC_SYNTHESIZE(Inventory::Type, inventoryType, InventoryType);
	InventoryBuffHandler* inventoryBuffHandler;

	cocos2d::Sprite* icon;
};

