#include "Character.h"
#include"GameScene.h"
#include"Attack.h"
#include"Dungeon.h"
#include"FieldEnum.h"
#include"Inventory.h"
#include "Weapon.h"
#include "Armor.h"
#include "Accessory.h"

USING_NS_CC;
using namespace Field;

void Character::sufferDamage(int damage)
{
	curHP -= damage;
	if (curHP <= 0)
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
	cocos2d::Point position = sprite->getPosition();

	CCActionInterval* moveAction = CCMoveTo::create(0.2, cocos2d::Vec2(position.x, position.y + 32));

	CCAnimate* action = CCAnimate::create(moveUpAnimation);
	action->setDuration(0.2);
	sprite->runAction(action);
	sprite->runAction(moveAction);

	setMapCoord(cocos2d::Point(mapCoord.x, mapCoord.y - 1));

	setOrientation(Orientation::UP);

	Point tarMapCoord = getMapCoord();
	tarMapCoord.y = tarMapCoord.y - 1;
	Dungeon::getInstance()->characterMove(getMapCoord(), tarMapCoord);
}

void Character::moveDown()
{
	cocos2d::Point position = sprite->getPosition();

	CCActionInterval* moveAction = CCMoveTo::create(0.2, cocos2d::Vec2(position.x, position.y - 32));

	CCAnimate* action = CCAnimate::create(moveDownAnimation);
	action->setDuration(0.2);
	sprite->runAction(action);
	sprite->runAction(moveAction);

	setMapCoord(cocos2d::Point(mapCoord.x, mapCoord.y + 1));

	setOrientation(Orientation::DOWN);

	Point tarMapCoord = getMapCoord();
	tarMapCoord.y = tarMapCoord.y + 1;
	Dungeon::getInstance()->characterMove(getMapCoord(), tarMapCoord);
}

void Character::moveLeft()
{
	cocos2d::Point position = sprite->getPosition();

	CCActionInterval* moveAction = CCMoveTo::create(0.2, cocos2d::Vec2(position.x - 32, position.y));

	CCAnimate* action = CCAnimate::create(moveLeftAnimation);
	action->setDuration(0.2);
	sprite->runAction(action);
	sprite->runAction(moveAction);

	setMapCoord(cocos2d::Point(mapCoord.x - 1, mapCoord.y));

	setOrientation(Orientation::LEFT);

	Point tarMapCoord = getMapCoord();
	tarMapCoord.x = tarMapCoord.x - 1;
	Dungeon::getInstance()->characterMove(getMapCoord(), tarMapCoord);
}

void Character::moveRight()
{
	cocos2d::Point position = sprite->getPosition();

	CCActionInterval* moveAction = CCMoveTo::create(0.2, cocos2d::Vec2(position.x + 32, position.y));

	CCAnimate* action = CCAnimate::create(moveRightAnimation);
	action->setDuration(0.2);
	sprite->runAction(action);
	sprite->runAction(moveAction);

	setMapCoord(cocos2d::Point(mapCoord.x + 1, mapCoord.y));

	setOrientation(Orientation::RIGHT);

	Point tarMapCoord = getMapCoord();
	tarMapCoord.x = tarMapCoord.x + 1;
	Dungeon::getInstance()->characterMove(getMapCoord(), tarMapCoord);
}

void Character::setOrientationUp()
{
	CCAnimate* action = CCAnimate::create(standUpAnimation);
	action->setDuration(0.1);
	sprite->runAction(action);
	setOrientation(Orientation::UP);
}

void Character::setOrientationDown()
{
	CCAnimate* action = CCAnimate::create(standDownAnimation);
	action->setDuration(0.1);
	sprite->runAction(action);
	setOrientation(Orientation::DOWN);
}

void Character::setOrientationLeft()
{
	CCAnimate* action = CCAnimate::create(standLeftAnimation);
	action->setDuration(0.1);
	sprite->runAction(action);
	setOrientation(Orientation::LEFT);
}

void Character::setOrientationRight()
{
	CCAnimate* action = CCAnimate::create(standRightAnimation);
	action->setDuration(0.1);
	sprite->runAction(action);
	setOrientation(Orientation::RIGHT);
}

void Character::equipLeftHand(Weapon* inventory)
{
	CCAssert(inventory, "null inventory to equip");
	leftHand = inventory;
	inventory->equip(this);
}

void Character::unequipLeftHand()
{
	if (leftHand)
	{
		leftHand->unequip(this);
	}
	leftHand = nullptr;
}

void Character::equipRightHand(Weapon* inventory)
{
	CCAssert(inventory, "null inventory to equip");
	rightHand = inventory;
	inventory->equip(this);
}

void Character::unequipRightHand()
{
	if (rightHand)
	{
		rightHand->unequip(this);
	}
	rightHand = nullptr;
}


cocos2d::Point Character::getPosition()
{
	return sprite->getPosition();
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

void Character::addInventory(Inventory * inventory)
{
	inventoryList.push_back(inventory);
}

std::vector<Inventory*>& Character::getInventoryList()
{
	return inventoryList;
}

CCSprite * Character::getSprite()
{
	return sprite;
}

void Character::setSprite(std::string spriteName)
{
	sprite = CCSprite::createWithSpriteFrameName(spriteName);
	sprite->retain();
}

int Character::getAttack()
{
	return 10;
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
}

Character::~Character()
{
	sprite->release();
	moveUpAnimation->release();
	moveDownAnimation->release();
	moveLeftAnimation->release();
	moveRightAnimation->release();
}

bool Character::isMoveAble(cocos2d::Point position)
{
	Field::Storey* storey = Dungeon::getInstance()->getStorey();
	if (storey->getTile(position) == Field::Floor)
	{
		return true;
	}
	return false;
}


void Character::setMoveUpAnimation(cocos2d::CCAnimation* animation)
{
	moveUpAnimation = animation;
}

void Character::setMoveDownAnimation(cocos2d::CCAnimation* animation)
{
	moveDownAnimation = animation;
}

void Character::setMoveLeftAnimation(cocos2d::CCAnimation* animation)
{
	moveLeftAnimation = animation;
}

void Character::setMoveRightAnimation(cocos2d::CCAnimation* animation)
{
	moveRightAnimation = animation;
}

void Character::setStandUpAnimation(cocos2d::CCAnimation * animation)
{
	standUpAnimation = animation;
}

void Character::setStandDownAnimation(cocos2d::CCAnimation * animation)
{
	standDownAnimation = animation;
}

void Character::setStandLeftAnimation(cocos2d::CCAnimation * animation)
{
	standLeftAnimation = animation;
}

void Character::setStandRightAnimation(cocos2d::CCAnimation * animation)
{
	standRightAnimation = animation;
}