#include "HudEquipMenu.h"
#include "Player.h"
#include "HudMenuItem.h"
#include "InventoryManager.h"
#include "InventoryInHand.h"
#include "Armor.h"
#include "Accessory.h"



HudEquipMenu::HudEquipMenu(cocos2d::Rect rect)
	:HudMenu(rect)
{

}

HudEquipMenu::~HudEquipMenu()
{
}

void HudEquipMenu::update()
{
	clear();

	Character* characterPtr = Player::getInstance()->getcharacterPtr();

	InventoryInHand* leftInventory = characterPtr->getLeftHand();
	InventoryInHand* rightInventory = characterPtr->getRightHand();
	Armor* armor = characterPtr->getArmor();
	Accessory* accessory = characterPtr->getAccessory();

	std::string leftInventoryLabel = leftInventory ? leftInventory->getCname() : "empty";
	std::string rightInventoryLabel = rightInventory ? rightInventory->getCname() : "empty";
	std::string armorLabel = armor ? armor->getCname() : "empty";
	std::string accessoryLabel = accessory ? accessory->getCname() : "empty";

	HudMenuItem* leftInventoryItem = new HudMenuItem(leftInventoryLabel);
	HudMenuItem* rightInventoryItem = new HudMenuItem(rightInventoryLabel);
	HudMenuItem* armorInventoryItem = new HudMenuItem(armorLabel);
	HudMenuItem* accessoryInventoryItem = new HudMenuItem(accessoryLabel);

	this->addItem(leftInventoryItem);
	this->addItem(rightInventoryItem);
	this->addItem(armorInventoryItem);
	this->addItem(accessoryInventoryItem);
}

