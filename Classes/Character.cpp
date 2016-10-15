#include "Character.h"
#include"MainLayer.h"
#include"Dungeon.h"
#include"FieldEnum.h"
#include"Inventory.h"
#include "InventoryInHand.h"
#include "Weapon.h"
#include "Armor.h"
#include "Accessory.h"
#include "AIBase.h"
#include "InventoryHandler.h"
#include "SkillBase.h"
#include "Attack.h"
#include "Dungeon.h"
#include "FixedSelector.h"
#include "LinerSelector.h"
#include "SingleDirectionSearchSelector.h"

USING_NS_CC;
using namespace Field;

void Character::sufferDamage(int damage)
{
	HP -= damage;
	if (HP <= 0)
	{
		die();
	}
}

void Character::die()
{
	sprite->setVisible(false);
	dead = true;
}

bool Character::isDead()
{
	return dead;
}

void Character::moveUp()
{
	Dungeon::getInstance()->getStorey()->characterMoveUp(this);
}

void Character::moveDown()
{
	Dungeon::getInstance()->getStorey()->characterMoveDown(this);
}

void Character::moveLeft()
{
	Dungeon::getInstance()->getStorey()->characterMoveLeft(this);
}

void Character::moveRight()
{
	Dungeon::getInstance()->getStorey()->characterMoveRight(this);
}

void Character::setOrientationUp()
{
	Animate* action = Animate::create(standUpAnimation);
	action->setDuration(0.1);
	sprite->runAction(action);
	setOrientation(Orientation::UP);
}

void Character::setOrientationDown()
{
	Animate* action = Animate::create(standDownAnimation);
	action->setDuration(0.1);
	sprite->runAction(action);
	setOrientation(Orientation::DOWN);
}

void Character::setOrientationLeft()
{
	Animate* action = Animate::create(standLeftAnimation);
	action->setDuration(0.1);
	sprite->runAction(action);
	setOrientation(Orientation::LEFT);
}

void Character::setOrientationRight()
{
	Animate* action = Animate::create(standRightAnimation);
	action->setDuration(0.1);
	sprite->runAction(action);
	setOrientation(Orientation::RIGHT);
}


void Character::showMoveUpAnimation()
{
	Animate* action = Animate::create(moveUpAnimation);
	action->setDuration(0.2);
	sprite->runAction(action);
}

void Character::showMoveDownAnimation()
{
	Animate* action = Animate::create(moveDownAnimation);
	action->setDuration(0.2);
	sprite->runAction(action);
}

void Character::showMoveLeftAnimation()
{
	Animate* action = Animate::create(moveLeftAnimation);
	action->setDuration(0.2);
	sprite->runAction(action);
}

void Character::showMoveRightAnimation()
{
	Animate* action = Animate::create(moveRightAnimation);
	action->setDuration(0.2);
	sprite->runAction(action);
}

void Character::equipLeftHand(Inventory* inventory)
{
	inventory->equipLeftHand(this);
}

void Character::equipRightHand(Inventory* inventory)
{
	inventory->equipRightHand(this);
}

void Character::equipArmor(Inventory* inventory)
{
	inventory->equipArmor(this);
}

void Character::equipAccessory(Inventory* inventory)
{
	inventory->equipAccessory(this);
}

void Character::unequipLeftHand()
{
	if (leftHand && leftHand->getInventoryType()==Inventory::OneHandWeapon)
	{
		inventoryHandler->addInventory(leftHand);
		leftHand = nullptr;
	}
	else if (leftHand &&
		(leftHand->getInventoryType() == Inventory::TwoHandWeapon ||
			leftHand->getInventoryType() == Inventory::Bow))
	{
		inventoryHandler->addInventory(leftHand);
		leftHand = nullptr;
		rightHand = nullptr;
	}
}

void Character::unequipRightHand()
{
	if (rightHand && rightHand->getInventoryType()==Inventory::OneHandWeapon)
	{
		inventoryHandler->addInventory(rightHand);
		rightHand = nullptr;
	}
	else if (rightHand &&
		(rightHand->getInventoryType() == Inventory::TwoHandWeapon ||
			rightHand->getInventoryType() == Inventory::Bow))
	{
		inventoryHandler->addInventory(rightHand);
		leftHand = nullptr;
		rightHand = nullptr;
	}
}

void Character::unequipArmor()
{

}

void Character::unequipAccessory()
{

}


cocos2d::Point Character::getPosition()
{
	return sprite->getPosition();
}

cocos2d::Point Character::getWorldPosition()
{
	Node* layer = sprite->getParent();

	cocos2d::Point spritePosition = sprite->getPosition();
	cocos2d::Point layerPositioin = layer->getPosition();

	return spritePosition+layerPositioin;
}

void Character::setPosition(float x, float y)
{
	sprite->setPosition(x, y);
}

cocos2d::Node * Character::getParent()
{
	return sprite->getParent();
	
}

void Character::runSkill(std::string skillName)
{
	skillBox[skillName]->active();
}

std::vector<cocos2d::Point> Character::getAtkArea()
{
	std::vector<cocos2d::Point> vec;
	if ((leftHand && leftHand->getInventoryType() == Inventory::OneHandWeapon) ||
		(rightHand && rightHand->getInventoryType()==Inventory::OneHandWeapon)
		)
	{
		return getOneHandAtkArea();
	}
	else if (leftHand && leftHand->getInventoryType() == Inventory::TwoHandWeapon)
	{
		return getTwoHandAtkArea();
	}
	else if (leftHand && leftHand->getInventoryType() == Inventory::Bow)
	{
		return getBowAtkArea();
	}
	return vec;
}

InventoryHandler* Character::getInventoryHandler()
{
	return inventoryHandler;
}

void Character::addInventory(Inventory * inventory)
{
	inventoryHandler->addInventory(inventory);
}

void Character::addInventory(const std::string& inventoryName)
{
	inventoryHandler->addInventory(inventoryName, 1);
}

Sprite * Character::getSprite()
{
	return sprite;
}

void Character::setSprite(std::string spriteName)
{
	sprite = Sprite::createWithSpriteFrameName(spriteName);
	sprite->retain();
}


void Character::setAI(AIBase* a)
{
	ai = a;
	ai->setCharacter(this);
}

Character::Character()
{
	Skill::Attack* attack = new Skill::Attack(this);
	skillBox["attack"] = attack;

	orientation = DOWN;
	dead = false;

	leftHand = nullptr;
	rightHand = nullptr;
	armor = nullptr;
	accessory = nullptr;

	ai = nullptr;

	inventoryHandler = new InventoryHandler();
}

Character::~Character()
{
	sprite->release();
	moveUpAnimation->release();
	moveDownAnimation->release();
	moveLeftAnimation->release();
	moveRightAnimation->release();
	if (ai)
	{
		delete ai;
	}
}

void Character::update()
{
	if (ai)
	{
		ai->update();
	}
}


std::vector<cocos2d::Point> Character::getOneHandAtkArea()
{
	FixedSelector selector;
	selector.addRelativeCoord(cocos2d::Point(0, 1));
	return selector.select(this);

//	std::vector<cocos2d::Point> vec;
//	cocos2d::Point targetPosition=getMapCoord();

//	switch (orientation)
//	{
//	case Character::UP:
//		targetPosition.y -= 1;
//		break;
//	case Character::DOWN:
//		targetPosition.y += 1;
//		break;
//	case Character::LEFT:
//		targetPosition.x -= 1;
//		break;
//	case Character::RIGHT:
//		targetPosition.x += 1;
//		break;
//	default:
//		break;
//	}
//	vec.push_back(targetPosition);
//	return vec;
}

// x | x | x		
//-----------
//   | c |
//-----------
//   |   |
std::vector<cocos2d::Point> Character::getTwoHandAtkArea()
{
	FixedSelector selector;
	selector.addRelativeCoord(0, 1);
	selector.addRelativeCoord(-1, 1);
	selector.addRelativeCoord(1, 1);
	return selector.select(this);
}

std::vector<cocos2d::Point> Character::getBowAtkArea()
{
	SingleDirectionSearchSelector selector;
	selector.setImpactNumber(1);
	return selector.select(this);
}

void Character::setMoveUpAnimation(cocos2d::Animation* animation)
{
	moveUpAnimation = animation;
}

void Character::setMoveDownAnimation(cocos2d::Animation* animation)
{
	moveDownAnimation = animation;
}

void Character::setMoveLeftAnimation(cocos2d::Animation* animation)
{
	moveLeftAnimation = animation;
}

void Character::setMoveRightAnimation(cocos2d::Animation* animation)
{
	moveRightAnimation = animation;
}

void Character::setStandUpAnimation(cocos2d::Animation * animation)
{
	standUpAnimation = animation;
}

void Character::setStandDownAnimation(cocos2d::Animation * animation)
{
	standDownAnimation = animation;
}

void Character::setStandLeftAnimation(cocos2d::Animation * animation)
{
	standLeftAnimation = animation;
}

void Character::setStandRightAnimation(cocos2d::Animation * animation)
{
	standRightAnimation = animation;
}
