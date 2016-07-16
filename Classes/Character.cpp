#include "Character.h"
#include"GameScene.h"

USING_NS_CC;

Character * Character::create(const std::string & filename)
{
	Character* character = new Character();

	character->setFrameCache(filename);

	CCSprite* sp = CCSprite::createWithSpriteFrameName("Actor1_01.png");

	character->setSprite(sp);

	character->createMoveUpAnimation();
	character->createMoveDownAnimation();
	character->createMoveLeftAnimation();
	character->createMoveRightAnimation();
	character->createStopUpAnimation();
	character->createStopDownAnimation();
	character->createStopLeftAnimation();
	character->createStopRightAnimation();


	return character;
}

void Character::moveUp()
{
	cocos2d::Point position = sprite->getPosition();

	CCActionInterval* moveAction = CCMoveTo::create(2.0, cocos2d::Vec2(position.x, position.y + 32));

	sprite->runAction(moveAction);
	setMapCoord(cocos2d::Point(mapCoord.x, mapCoord.y - 1));
	scene->setViewPointCenter(sprite->getPosition());
}

void Character::moveDown()
{
}

void Character::moveLeft()
{
}

void Character::moveRight()
{
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
}

void Character::setFrameCache(std::string filename)
{
	cache=CCSpriteFrameCache::sharedSpriteFrameCache();
	cache->addSpriteFramesWithFile(filename);
}

void Character::createMoveUpAnimation()
{
	Vector< SpriteFrame* > sfme = Vector< SpriteFrame* >::Vector();
	char str[20] = { 0 };
	for (int i = 10; i < 13; ++i)
	{
		sprintf(str, "Actor1_%02d.png", i);
		SpriteFrame *fname = cache->spriteFrameByName(str);
		sfme.pushBack(fname);
	}
	moveUpAnimation = CCAnimation::createWithSpriteFrames(sfme, 0.1f);
}

void Character::createMoveDownAnimation()
{
	Vector< SpriteFrame* > sfme = Vector< SpriteFrame* >::Vector();
	char str[20] = { 0 };
	for (int i = 1; i < 4; ++i)
	{
		sprintf(str, "Actor1_%02d.png", i);
		SpriteFrame *fname = cache->spriteFrameByName(str);
		sfme.pushBack(fname);
	}
	moveDownAnimation = CCAnimation::createWithSpriteFrames(sfme, 0.1f);
}

void Character::createMoveLeftAnimation()
{
	Vector< SpriteFrame* > sfme = Vector< SpriteFrame* >::Vector();
	char str[20] = { 0 };
	for (int i = 4; i < 7; ++i)
	{
		sprintf(str, "Actor1_%02d.png", i);
		SpriteFrame *fname = cache->spriteFrameByName(str);
		sfme.pushBack(fname);
	}
	moveLeftAnimation = CCAnimation::createWithSpriteFrames(sfme, 0.1f);
}

void Character::createMoveRightAnimation()
{
	Vector< SpriteFrame* > sfme = Vector< SpriteFrame* >::Vector();
	char str[20] = { 0 };
	for (int i = 7; i < 10; ++i)
	{
		sprintf(str, "Actor1_%02d.png", i);
		SpriteFrame *fname = cache->spriteFrameByName(str);
		sfme.pushBack(fname);
	}
	moveRightAnimation = CCAnimation::createWithSpriteFrames(sfme, 0.1f);
}

void Character::createStopUpAnimation()
{
	Vector<SpriteFrame* > sfme = Vector<SpriteFrame*>::Vector();
	char str[20] = { 0 };
	sprintf(str, "Actor1_10.png");
	SpriteFrame *fname = cache->spriteFrameByName(str);
	sfme.pushBack(fname);
	stopUpAnimation = CCAnimation::createWithSpriteFrames(sfme, 0.1f);
}

void Character::createStopDownAnimation()
{
	Vector<SpriteFrame* > sfme = Vector<SpriteFrame*>::Vector();
	char str[20] = { 0 };
	sprintf(str, "Actor1_01.png");
	SpriteFrame *fname = cache->spriteFrameByName(str);
	sfme.pushBack(fname);
	stopDownAnimation = CCAnimation::createWithSpriteFrames(sfme, 0.1f);
}

void Character::createStopLeftAnimation()
{
	Vector<SpriteFrame* > sfme = Vector<SpriteFrame*>::Vector();
	char str[20] = { 0 };
	sprintf(str, "Actor1_04.png");
	SpriteFrame *fname = cache->spriteFrameByName(str);
	sfme.pushBack(fname);
	stopLeftAnimation = CCAnimation::createWithSpriteFrames(sfme, 0.1f);
}

void Character::createStopRightAnimation()
{
	Vector<SpriteFrame* > sfme = Vector<SpriteFrame*>::Vector();
	char str[20] = { 0 };
	sprintf(str, "Actor1_07.png");
	SpriteFrame *fname = cache->spriteFrameByName(str);
	sfme.pushBack(fname);
	stopRightAnimation = CCAnimation::createWithSpriteFrames(sfme, 0.1f);
}
