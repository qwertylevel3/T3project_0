#include "HudMenuItem.h"



HudMenuItem::HudMenuItem(cocos2d::Rect rect)
{
	sprite = cocos2d::Sprite::create("menu.png", rect);
	sprite->retain();
	curIndex = 0;
	marginal.x = 10;
	marginal.y = 10;
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
	itemLabel->setMaxLineWidth(getWidth() - 2 * marginal.x);

	//ÉèÖÃ×ø±êÎª×øÉÏ½Ç¶ÔÆë
	cocos2d::Point position;
	position.x = itemLabel->getMaxLineWidth()/2;
	position.y = getHeight()-itemLabel->getLineHeight()/2;

	//Æ«ÒÆ±ß¿ò¿í¶È
	position.x += marginal.x;
	position.y -= marginal.y;

	//Æ«ÒÆÐòÁÐÊý
	position.y -= index*itemLabel->getLineHeight();

	itemLabel->setPosition(position.x, position.y);
	labelList.push_back(itemLabel);
}

cocos2d::Sprite * HudMenuItem::getSprite()
{
	return sprite;
}

void HudMenuItem::setPosition(cocos2d::Point position)
{
	position.x += getWidth()/2;
	position.y -= getHeight()/2;
	sprite->setPosition(position);
}

int HudMenuItem::getWidth()
{
	return sprite->getTextureRect().size.width;
}

int HudMenuItem::getHeight()
{
	return sprite->getTextureRect().size.height;
}
