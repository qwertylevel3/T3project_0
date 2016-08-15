#include "HudMenuItem.h"
#include"ToolFunction.h"
#include"HudCursor.h"
#include"HudLayer.h"



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
	curIndex = curIndex == 0 ? curIndex : curIndex - 1;
	chooseChildItem(curIndex);

}

void HudMenuItem::handleDown()
{
	curIndex = curIndex == childList.size() - 1 ? curIndex : curIndex + 1;
	chooseChildItem(curIndex);
}

void HudMenuItem::handleLeft()
{
}

void HudMenuItem::handleRight()
{
}

void HudMenuItem::initCursor()
{
	chooseChildItem(0);
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
	cocos2d::Label* itemLabel = cocos2d::Label::createWithTTF(item->getUTF8name(), "fonts/arialuni.ttf", 24);
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

cocos2d::Point HudMenuItem::getPosition()
{
	return sprite->getPosition();
}

int HudMenuItem::getWidth()
{
	return sprite->getTextureRect().size.width;
}

int HudMenuItem::getHeight()
{
	return sprite->getTextureRect().size.height;
}

std::string HudMenuItem::getUTF8name()
{
	return ToolFunction::WStr2UTF8(getName());
}

void HudMenuItem::chooseChildItem(int index)
{
	curIndex = index;

	cocos2d::Point position = labelList[curIndex]->getPosition();
//	position = labelList[curIndex]->convertToWorldSpace(position);
//	position = HudLayer::getInstance()->convertToNodeSpace(position);
	position.x -= labelList[curIndex]->getMaxLineWidth() / 2;
	position.x -= HudCursor::getInstance()->getSprite()->getTextureRect().size.width / 2;

	HudCursor::getInstance()->setPosition(position);
}
