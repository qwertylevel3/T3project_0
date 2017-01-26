#include "Inventory.h"
#include"cocos2d.h"
#include "InventoryBuffHandler.h"
#include "ToolFunction.h"
#include "BuffFactory.h"
#include "BuffBase.h"

USING_NS_CC;

Inventory::Inventory()
{
	icon = nullptr;
	inventoryBuffHandler = new InventoryBuffHandler();
}

Inventory::~Inventory()
{
	delete inventoryBuffHandler;
}

void Inventory::equipLeftHand(Character* character)
{
}

void Inventory::unequipLeftHand(Character* character)
{
}

void Inventory::equipRightHand(Character* character)
{
}

void Inventory::unequipRightHand(Character* character)
{
}

void Inventory::equipArmor(Character* character)
{
}

void Inventory::equipAccessory(Character* character)
{
}

void Inventory::load(Character* character)
{
}

void Inventory::unload(Character* character)
{
}

void Inventory::use(Character* character)
{
}

void Inventory::copyData(Inventory* inventory)
{
	inventory->setName(name);
	inventory->setCname(cname);
	inventory->setTips(tips);
	inventory->setLevel(level);
	inventory->setPrice(price);
	inventory->setWeight(weight);
	inventory->setSpriteName(spriteName);
	inventory->setInventoryType(inventoryType);

	for each (std::string buffID in inventoryBuffHandler->getBuffIDBox())
	{
		inventory->addBuff(buffID);
	}
}

cocos2d::Sprite* Inventory::getIcon()
{
	CCAssert(!spriteName.empty(), std::string(name + " sprite name is empty").c_str());
	if (!icon)
	{
		icon = CCSprite::createWithSpriteFrameName(spriteName);
	}
	return icon;
}

void Inventory::addBuff(std::string buffID)
{
	inventoryBuffHandler->addBuff(buffID);
}

std::vector<std::string> Inventory::getAllInventoryBuff()
{
	return inventoryBuffHandler->getBuffIDBox();
}

std::string Inventory::getBaseDescription()
{
	std::string description;

	description += ToolFunction::WStr2UTF8(L"类型:") + getTypeStr()+ "\n";
	description += "Level:" + ToolFunction::int2string(level)+"\n";
	description += "Weight:" + ToolFunction::int2string(weight) + "\n\n";

	description += tips+"\n\n";

	if (!getAllInventoryBuff().empty())
	{
		description += ToolFunction::WStr2UTF8(L"附加buff:\n");

		std::vector<std::string > allBuff = getAllInventoryBuff();

		int count=1;
		for each (std::string  buffID in allBuff)
		{
			Buff::BuffBase* buff = Buff::BuffFactory::getInstance()->getBuff(buffID);

			description += ToolFunction::int2string(count)+"."+
				buff->getDescription()+"\n";
			count++;
		}
		return description;
	}
	return description;
}

std::string Inventory::getExtraDescription()
{
	return "";
}

std::string Inventory::getDescription()
{
	return getBaseDescription() + getExtraDescription();
}

std::string Inventory::getTypeStr()
{
	std::string typeStr;
	switch (inventoryType)
	{
	case Inventory::Other:
		typeStr = ToolFunction::WStr2UTF8(L"其他类型");
		break;
	case Inventory::OneHandWeapon:
		typeStr = ToolFunction::WStr2UTF8(L"装备");
		break;
	case Inventory::TwoHandWeapon:
		typeStr = ToolFunction::WStr2UTF8(L"装备");
		break;
	case Inventory::Bow:
		typeStr = ToolFunction::WStr2UTF8(L"装备");
		break;
	case Inventory::Shield:
		typeStr = ToolFunction::WStr2UTF8(L"装备");
		break;
	case Inventory::Arrow:
		typeStr = ToolFunction::WStr2UTF8(L"箭");
		break;
	case Inventory::Armor:
		typeStr = ToolFunction::WStr2UTF8(L"护甲");
		break;
	case Inventory::Supply:
		typeStr = ToolFunction::WStr2UTF8(L"物品");
		break;
	case Inventory::Accessory:
		typeStr = ToolFunction::WStr2UTF8(L"附件");
		break;
	case Inventory::Note:
		typeStr = ToolFunction::WStr2UTF8(L"书");
		break;
	default:
		typeStr = ToolFunction::WStr2UTF8(L"其他物品");
		break;
	}
	return typeStr;
}
