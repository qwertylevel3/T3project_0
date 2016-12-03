#include "HudCursor.h"
#include"cocos2d.h"
#include"HudMenu.h"

USING_NS_CC;

HudCursor::HudCursor()
{
	//	sprite = CCSprite::create("HUD/cursor.png");
	sprite = cocos2d::Sprite::create();

	cocos2d::SpriteFrameCache::getInstance()->addSpriteFramesWithFile("HUD/cursor.plist");
}

HudCursor::~HudCursor()
{
	sprite->release();
}

void HudCursor::setPosition(cocos2d::Point position)
{
	sprite->setPosition(position);
}

void HudCursor::handleKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_ENTER:
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		handleRight();
		break;
	case EventKeyboard::KeyCode::KEY_ESCAPE:
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		handleLeft();
		break;
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
		handleUp();
		break;
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		handleDown();
		break;
	}
}

void HudCursor::moveUp(int offset)
{
	cocos2d::Point position = sprite->getPosition();
	sprite->setPosition(cocos2d::Point(position.x, position.y + offset));
	showAnimation();
}

void HudCursor::moveDown(int offset)
{
	cocos2d::Point position = sprite->getPosition();
	sprite->setPosition(cocos2d::Point(position.x, position.y - offset));
	showAnimation();
}

void HudCursor::show()
{
	sprite->setVisible(true);
	showAnimation();
}

void HudCursor::hide()
{
	sprite->setVisible(false);
}

cocos2d::Sprite * HudCursor::getSprite()
{
	return sprite;
}

void HudCursor::setCurMenu(HudMenu* menu)
{
	cocos2d::Node* parent = sprite->getParent();
	if (parent)
	{
		parent->removeChild(sprite);
	}
	curMenu = menu;
	menu->getListView()->addChild(sprite, 2);
	menu->initCursor();
	showAnimation();
}

void HudCursor::handleLeft()
{
	curMenu->handleLeft();
}

void HudCursor::handleRight()
{
	curMenu->handleRight();
}

void HudCursor::handleUp()
{
	curMenu->handleUp();
}

void HudCursor::handleDown()
{
	curMenu->handleDown();
}

void HudCursor::showAnimation()
{

	Vector< SpriteFrame* > sfme = Vector< SpriteFrame* >::Vector();

	SpriteFrame *fname1 = CCSpriteFrameCache::getInstance()->getSpriteFrameByName("cursor1.png");
	SpriteFrame *fname2 = CCSpriteFrameCache::getInstance()->getSpriteFrameByName("cursor2.png");
	SpriteFrame *fname3 = CCSpriteFrameCache::getInstance()->getSpriteFrameByName("cursor3.png");
	SpriteFrame *fname4 = CCSpriteFrameCache::getInstance()->getSpriteFrameByName("cursor4.png");
	SpriteFrame *fname5 = CCSpriteFrameCache::getInstance()->getSpriteFrameByName("cursor5.png");

	sfme.pushBack(fname1);
	sfme.pushBack(fname2);
	sfme.pushBack(fname3);
	sfme.pushBack(fname4);
	sfme.pushBack(fname5);
	cocos2d::Animation::createWithSpriteFrames(sfme, 0.1f);

	sprite->retain();

	sprite->runAction(
		cocos2d::RepeatForever::create(
			cocos2d::Animate::create(
				cocos2d::Animation::createWithSpriteFrames(sfme, 0.1f)
			)
		)
	);

}
