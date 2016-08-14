#include "HudMenuItem.h"



HudMenuItem::HudMenuItem(cocos2d::Rect rect)
{
	sprite = cocos2d::Sprite::create("menu.png", rect);
	sprite->retain();
	curIndex = 0;
}


HudMenuItem::~HudMenuItem()
{
	sprite->release();
}

void HudMenuItem::handleUp()
{
}

void HudMenuItem::handleDown()
{
}

void HudMenuItem::handleLeft()
{
}

void HudMenuItem::handleRight()
{
}

void HudMenuItem::show()
{
	sprite->setVisible(true);
	for (int i = 0; i < labelList.size(); i++)
	{
		labelList[i]->setVisible(true);
	}
}

void HudMenuItem::hide()
{
	sprite->setVisible(false);
	for (int i = 0; i < labelList.size(); i++)
	{
		labelList[i]->setVisible(false);
	}
}

void HudMenuItem::addChildItem(HudMenuItem * item)
{
	int index = childList.size();
	childList.push_back(item);
	cocos2d::Label* itemLabel = cocos2d::Label::createWithTTF(item->getName(), "fonts/arial.ttf", 24);
	sprite->addChild(itemLabel);
	itemLabel->setPosition(60,500-index*itemLabel->getLineHeight());
	labelList.push_back(itemLabel);
}

cocos2d::Sprite * HudMenuItem::getSprite()
{
	return sprite;
}

void HudMenuItem::setPosition(cocos2d::Point position)
{
	sprite->setPosition(position);
}
