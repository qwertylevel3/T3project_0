#include "HudMenu.h"
#include"HudMenuItem.h"
#include"HudCursor.h"
#include"HudLayer.h"
#include<string>
#include "HudCursor.h"



HudMenu::HudMenu(cocos2d::Rect rect)
{
	itemIndex = 0;
	sprite = cocos2d::Sprite::create("HUD/menu.png", rect);
	HudLayer::getInstance()->addChild(sprite, 2);
	marginal.x = 10;
	marginal.y = 10;
	parent = nullptr;

	hide();
}


HudMenu::~HudMenu()
{
	clear();
	sprite->removeFromParent();
	removeFromParentMenu();
}

void HudMenu::update()
{

}

void HudMenu::handleUp()
{
	decreaseIndex();
	chooseItem(itemIndex);
}

void HudMenu::handleDown()
{
	increaseIndex();
	chooseItem(itemIndex);
}

void HudMenu::handleLeft()
{
	closeMenu();
}

void HudMenu::handleRight()
{
	activeChildMenu(itemIndex);
}

int HudMenu::getCurIndex()
{
	return itemIndex;
}

void HudMenu::show()
{
	sprite->setVisible(true);
	for (size_t i = 0; i < itemList.size(); i++)
	{
		itemList[i]->show();
	}
}

void HudMenu::hide()
{
	sprite->setVisible(false);
	for (size_t i = 0; i < itemList.size(); i++)
	{
		itemList[i]->hide();
	}
	for each (HudMenu* child in childMenu)
	{
		child->hide();
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
	chooseItem(itemIndex);
}

void HudMenu::addItem(HudMenuItem* item)
{
	item->setParentMenu(this);

	int index = itemList.size();
	itemList.push_back(item);

	cocos2d::Label* itemLabel = item->getLabel();
	sprite->addChild(itemLabel);
	item->setWidth(getWidth() - 2 * marginal.x);
	//itemLabel->setMaxLineWidth(getWidth() - 2 * marginal.x);

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

void HudMenu::setWidth(int w)
{
	sprite->setTextureRect(cocos2d::Rect(0,0,w,getHeight()));
	for each (HudMenuItem* item in itemList)
	{
		item->setWidth(w);
	}
}

void HudMenu::setHeight(int h)
{
	sprite->setTextureRect(cocos2d::Rect(0,0,getWidth(),h));
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
	if (itemList.empty())
	{
		HudCursor::getInstance()->hide();
		return;
	}

	itemIndex = index;

	itemIndex = itemIndex > itemList.size() - 1 ? itemList.size()-1 : itemIndex;
	itemIndex = itemIndex < 0 ? 0 : itemIndex;



	cocos2d::Point position = itemList[itemIndex]->getPosition();
//	position = labelList[curIndex]->convertToWorldSpace(position);
//	position = HudLayer::getInstance()->convertToNodeSpace(position);
	position.x -= itemList[itemIndex]->getWidth() / 2;
	position.x -= HudCursor::getInstance()->getSprite()->getTextureRect().size.width / 2;

	HudCursor::getInstance()->setPosition(position);
}

void HudMenu::activeChildMenu(int index)
{
	if (itemList.empty())
	{
		return;
	}
	itemList[index]->active();
}

void HudMenu::setParent(HudMenu* p)
{
	parent = p;
	p->addChildMenu(this);
}

void HudMenu::addChildMenu(HudMenu* c)
{
	childMenu.push_back(c);
}

void HudMenu::closeMenu()
{
	if (!parent)
	{
		return;
	}
	hide();
	HudCursor::getInstance()->setCurMenu(parent);
	parent->update();
}

void HudMenu::increaseIndex()
{
	itemIndex = itemIndex == itemList.size() - 1 ? itemIndex : itemIndex + 1;
}

void HudMenu::decreaseIndex()
{
	itemIndex = itemIndex == 0 ? itemIndex : itemIndex - 1;
}


void HudMenu::removeFromParentMenu()
{
	if (parent)
	{
		parent->removeChild(this);
	}
}

void HudMenu::clear()
{
	for (size_t i = 0; i < itemList.size(); i++)
	{
		delete itemList[i];
	}
	itemList.clear();
}

int HudMenu::getMarginalWidth()
{
	return marginal.x;
}

int HudMenu::getMarginalHeight()
{
	return marginal.y;
}

void HudMenu::removeChild(HudMenu* c)
{
	std::vector<HudMenu*>::iterator iter = childMenu.begin();
	while (iter != childMenu.end())
	{
		if (*iter == c)
		{
			childMenu.erase(iter);
			return;
		}
	}
}
