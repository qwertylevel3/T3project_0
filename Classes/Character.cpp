#include "Character.h"
#include"GameScene.h"
#include"Attack.h"
#include"Dungeon.h"
#include"FieldEnum.h"
#include"Inventory.h"
#include "InventoryInHand.h"
#include "Weapon.h"
#include "Armor.h"
#include "Accessory.h"
#include "AIBase.h"
#include "InventoryHandler.h"

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

std::vector<cocos2d::Point > Character::getLeftHandAtkArea()
{
	std::vector<cocos2d::Point> atkArea;
	if (!leftHand)
	{
		return atkArea;
	}
	if (leftHand->getInventoryType()==Inventory::OneHandWeapon 
		|| leftHand->getInventoryType()==Inventory::TwoHandWeapon)
	{
		Weapon* weapon = static_cast<Weapon*>(leftHand);
		return weapon->getAtkArea(this);
	}
	return atkArea;
}

std::vector<cocos2d::Point > Character::getRightHandAtkArea()
{
	std::vector<cocos2d::Point> atkArea;
	if (!rightHand)
	{
		return atkArea;
	}
	if (rightHand->getInventoryType()==Inventory::OneHandWeapon 
		|| rightHand->getInventoryType()==Inventory::TwoHandWeapon)
	{
		Weapon* weapon = static_cast<Weapon*>(rightHand);
		return weapon->getAtkArea(this);
	}
	return atkArea;
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
	skillBox[skillName]->run();
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
	Attack* attack = new Attack(this);
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

