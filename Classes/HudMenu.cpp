#include "HudMenu.h"
#include"HudMenuItem.h"
#include"HudCursor.h"
#include"HudLayer.h"
#include<string>
#include "HudCursor.h"



HudMenu::HudMenu(cocos2d::Rect rect)
{
	itemIndex = 0;
	sprite = cocos2d::Sprite::create("menu.png", rect);
	sprite->retain();
	marginal.x = 10;
	marginal.y = 10;
}


HudMenu::~HudMenu()
{
	sprite->release();
}

void HudMenu::handleUp()
{
	itemIndex = itemIndex == 0 ? itemIndex : itemIndex - 1;
	chooseItem(itemIndex);
}

void HudMenu::handleDown()
{
	itemIndex = itemIndex == itemList.size() - 1 ? itemIndex : itemIndex + 1;
	chooseItem(itemIndex);
}

void HudMenu::handleLeft()
{

}

void HudMenu::handleRight()
{

}

void HudMenu::show()
{
	sprite->setVisible(true);
	for (int i = 0; i < itemList.size(); i++)
	{
		itemList[i]->show();
	}
}

void HudMenu::hide()
{
	sprite->setVisible(false);
	for (int i = 0; i < itemList.size(); i++)
	{
		itemList[i]->hide();
	}
}

void HudMenu::setPosition(int x, int y)
{
	sprite->setPosition(x, y);
}

void HudMenu::setCursorPosition(int index)
{

}

void HudMenu::initCursor()
{
	chooseItem(0);
}

void HudMenu::addItem(HudMenuItem* item)
{
	int index = itemList.size();
	itemList.push_back(item);

	cocos2d::Label* itemLabel = item->getLabel();
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
}

int HudMenu::getWidth()
{
	return sprite->getTextureRect().size.width;
}

int HudMenu::getHeight()
{
	return sprite->getTextureRect().size.height;
}

cocos2d::Sprite* HudMenu::getSprite()
{
	return sprite;
}

void HudMenu::chooseItem(int index)
{
	itemIndex = index;

	cocos2d::Point position = itemList[itemIndex]->getPosition();
//	position = labelList[curIndex]->convertToWorldSpace(position);
//	position = HudLayer::getInstance()->convertToNodeSpace(position);
	position.x -= itemList[itemIndex]->getWidth() / 2;
	position.x -= HudCursor::getInstance()->getSprite()->getTextureRect().size.width / 2;

	HudCursor::getInstance()->setPosition(position);
}
