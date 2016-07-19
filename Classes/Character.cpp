#include "Character.h"
#include"GameScene.h"

USING_NS_CC;

void Character::moveUp()
{
	cocos2d::Point position = sprite->getPosition();

	CCActionInterval* moveAction = CCMoveTo::create(0.2, cocos2d::Vec2(position.x, position.y + 32));

	CCAnimate* action = CCAnimate::create(moveUpAnimation);
	action->setDuration(0.2);
	sprite->runAction(action);
	sprite->runAction(moveAction);

	setMapCoord(cocos2d::Point(mapCoord.x, mapCoord.y - 1));
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
}

cocos2d::Point Character::getPosition()
{
	return sprite->getPosition();
}

void Character::setPosition(float x, float y)
{
	sprite->setPosition(x, y);
}

Character::Character()
{
}


Character::~Character()
{
	moveUpAnimation->release();
	moveDownAnimation->release();
	moveLeftAnimation->release();
	moveRightAnimation->release();
}

void Character::createMoveUpAnimation()
{
	Vector< SpriteFrame* > sfme = Vector< SpriteFrame* >::Vector();
	char str[20] = { 0 };
	for (int i = 10; i < 13; ++i)
	{
		sprintf(str, "Actor1_%02d.png", i);
		SpriteFrame *fname = CCSpriteFrameCache::getInstance()->getSpriteFrameByName(str);
		sfme.pushBack(fname);
	}
	moveUpAnimation = CCAnimation::createWithSpriteFrames(sfme, 0.1f);
	moveUpAnimation->retain();
}

void Character::createMoveDownAnimation()
{
	Vector< SpriteFrame* > sfme = Vector< SpriteFrame* >::Vector();
	char str[20] = { 0 };
	for (int i = 1; i < 4; ++i)
	{
		sprintf(str, "Actor1_%02d.png", i);
		SpriteFrame *fname = CCSpriteFrameCache::getInstance()->getSpriteFrameByName(str);
		sfme.pushBack(fname);
	}
	moveDownAnimation = CCAnimation::createWithSpriteFrames(sfme, 0.1f);
	moveDownAnimation->retain();
}

void Character::createMoveLeftAnimation()
{
	Vector< SpriteFrame* > sfme = Vector< SpriteFrame* >::Vector();
	char str[20] = { 0 };
	for (int i = 4; i < 7; ++i)
	{
		sprintf(str, "Actor1_%02d.png", i);
		SpriteFrame *fname = CCSpriteFrameCache::getInstance()->getSpriteFrameByName(str);
		sfme.pushBack(fname);
	}
	moveLeftAnimation = CCAnimation::createWithSpriteFrames(sfme, 0.1f);
	moveLeftAnimation->retain();
}

void Character::createMoveRightAnimation()
{
	Vector< SpriteFrame* > sfme = Vector< SpriteFrame* >::Vector();
	char str[20] = { 0 };
	for (int i = 7; i < 10; ++i)
	{
		sprintf(str, "Actor1_%02d.png", i);
		SpriteFrame *fname = CCSpriteFrameCache::getInstance()->getSpriteFrameByName(str);
		sfme.pushBack(fname);
	}
	moveRightAnimation = CCAnimation::createWithSpriteFrames(sfme, 0.1f);
	moveRightAnimation->retain();
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
