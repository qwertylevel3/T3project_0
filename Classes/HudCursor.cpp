#include "HudCursor.h"
#include"cocos2d.h"
#include"HudMenuItem.h"


USING_NS_CC;

HudCursor::HudCursor()
{
	sprite = CCSprite::create("cursor.png");
	sprite->retain();
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
}

void HudCursor::moveDown(int offset)
{
	cocos2d::Point position = sprite->getPosition();
	sprite->setPosition(cocos2d::Point(position.x, position.y - offset));
}

void HudCursor::show()
{
	sprite->setVisible(true);
}

void HudCursor::hide()
{
	sprite->setVisible(false);
}

cocos2d::Sprite * HudCursor::getSprite()
{
	return sprite;
}

void HudCursor::setCurItem(HudMenuItem * item)
{
	cocos2d::Node* parent = sprite->getParent();
	if (parent)
	{
		parent->removeChild(sprite);
	}
	curItem = item;
	item->getSprite()->addChild(sprite, 2);
	item->initCursor();
}

void HudCursor::handleLeft()
{
	curItem->handleLeft();
}

void HudCursor::handleRight()
{
	curItem->handleRight();
}

void HudCursor::handleUp()
{
	curItem->handleUp();
}

void HudCursor::handleDown()
{
	curItem->handleDown();
}
