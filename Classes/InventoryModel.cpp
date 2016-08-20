#include "InventoryModel.h"
#include"cocos2d.h"
#include"Weapon.h"
#include"Armor.h"
#include"Accessory.h"
#include"Supply.h"

USING_NS_CC;



InventoryModel::InventoryModel()
{
}


InventoryModel::~InventoryModel()
{
}

Inventory * InventoryModel::makeInventory()
{
	Inventory* inv;
	if (type == "weapon")
	{
		inv = makeWeapon();
	}
	else if (type == "armor")
	{
		inv = makeArmor();
	}
	else if (type == "Accessory")
	{
		inv = makeAccessory();
	}
	else if (type == "Supply")
	{
		inv = makeSupply();
	}
	else
	{
		CCAssert(false, "unknow inventory type");
	}

	inv->setName(name);
	inv->setCname(cname);
	inv->setPrice(price);
	inv->setWeight(weight);
	inv->setIcon(CCSprite::createWithSpriteFrameName(spriteName));

	inv->setEvadeProAdd(evadeProAdd);
	inv->setAccuracyProAdd(accuracyProAdd);
	inv->setCriticalAdd(criticalAdd);
	inv->setCriticalProAdd(criticalProAdd);
	inv->setBlockAdd(blockAdd);
	inv->setBlockProAdd(blockProAdd);
	inv->setComboProAdd(comboProAdd);

	return inv;
}

Weapon * InventoryModel::makeWeapon()
{
	Weapon* weapon = new Weapon();
	return weapon;
}

Accessory * InventoryModel::makeAccessory()
{
	Accessory* accessory = new Accessory();
	return accessory;
}

Armor * InventoryModel::makeArmor()
{
	Armor* armor = new Armor();
	return armor;
}

Supply * InventoryModel::makeSupply()
{
	Supply* supply = new Supply();
	return supply;
}
