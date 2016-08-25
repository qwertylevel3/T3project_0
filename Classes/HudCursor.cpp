#include "HudCursor.h"
#include"cocos2d.h"
#include"HudMenu.h"


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

void HudCursor::setCurMenu(HudMenu* menu)
{
	cocos2d::Node* parent = sprite->getParent();
	if (parent)
	{
		parent->removeChild(sprite);
	}
	curMenu = menu;
	menu->getSprite()->addChild(sprite, 2);
	menu->initCursor();
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
