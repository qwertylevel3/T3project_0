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

void HudCursor::handleKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_ENTER:
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		curItem->handleRight();
		break;
	case EventKeyboard::KeyCode::KEY_ESCAPE:
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		curItem->handleLeft();
		break;
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
		moveUp();
		curItem->handleUp();
		break;
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		moveDown();
		curItem->handleDown();
		break;
	}
}

void HudCursor::moveUp()
{
	cocos2d::Point position = sprite->getPosition();
	sprite->setPosition(cocos2d::Point(position.x, position.y + 24));
}

void HudCursor::moveDown()
{
	cocos2d::Point position = sprite->getPosition();
	sprite->setPosition(cocos2d::Point(position.x, position.y - 24));
}
