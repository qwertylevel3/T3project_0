#include "HudMenu.h"
#include"HudMenuItem.h"
#include"HudCursor.h"
#include"HudLayer.h"
#include<string>
#include "HudCursor.h"



HudMenu::HudMenu(cocos2d::Rect rect)
{
	itemIndex = 0;

	layout = cocos2d::ui::Layout::create();
//	layout->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE);
	layout->setAnchorPoint(cocos2d::Vec2::ANCHOR_TOP_LEFT);
	layout->setBackGroundImage("HUD/menu.png");
	layout->setBackGroundImageScale9Enabled(true);
	layout->setSize(rect.size);
	layout->setOpacity(180);
	


	listView = cocos2d::ui::ListView::create();
	listView->setContentSize(
		cocos2d::Size(
			rect.size.width,
			rect.size.height//-20
		)
	);
	listView->setOpacity(255);
	listView->setAnchorPoint(cocos2d::Vec2::ANCHOR_BOTTOM_LEFT);
//	listView->setAnchorPoint(cocos2d::Vec2::ANCHOR_TOP_LEFT);
	listView->setBackGroundImageScale9Enabled(true);
	listView->setPosition(cocos2d::Vec2(20, 0));
	listView->setBounceEnabled(false);

	layout->addChild(listView);

	HudLayer::getInstance()->addChild(layout, 2);
	marginal.x = 10;
	marginal.y = 10;
	parent = nullptr;

	hide();
}


HudMenu::~HudMenu()
{
	clear();
	listView->removeFromParent();
//	sprite->removeFromParent();
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
	//sprite->setVisible(true);
	layout->setVisible(true);
	listView->setVisible(true);
	for (size_t i = 0; i < itemList.size(); i++)
	{
		itemList[i]->show();
	}
}

void HudMenu::hide()
{
	//sprite->setVisible(false);
	layout->setVisible(false);
	listView->setVisible(false);
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
	//sprite->setPosition(x, y);
	layout->setPosition(cocos2d::Vec2(x, y));
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

	cocos2d::ui::Text* itemLabel = item->getLabel();
//	sprite->addChild(itemLabel);
	listView->pushBackCustomItem(itemLabel);
	item->setWidth(getWidth() - 2 * marginal.x);
	//itemLabel->setMaxLineWidth(getWidth() - 2 * marginal.x);

//	//ÉèÖÃ×ø±êÎª×øÉÏ½Ç¶ÔÆë
//	cocos2d::Point position;
//	position.x = itemLabel->getWidth()/2;
//	position.y = getHeight()-itemLabel->getLineHeight()/2;

//	//Æ«ÒÆ±ß¿ò¿í¶È
//	position.x += marginal.x;
//	position.y -= marginal.y;

//	//Æ«ÒÆÐòÁÐÊý
//	position.y -= index*itemLabel->getLineHeight();

//	itemLabel->setPosition(position.x, position.y);
}

void HudMenu::setWidth(int w)
{
//	sprite->setTextureRect(cocos2d::Rect(0,0,w,getHeight()));

	layout->setSize(cocos2d::Size(w, layout->getSize().height));
	listView->setContentSize(cocos2d::Size(w, listView->getSize().height));

	for each (HudMenuItem* item in itemList)
	{
		item->setWidth(w);
	}
}

void HudMenu::setHeight(int h)
{
//	sprite->setTextureRect(cocos2d::Rect(0,0,getWidth(),h));
	layout->setSize(cocos2d::Size(layout->getSize().width,h));
	listView->setContentSize(cocos2d::Size(listView->getSize().width,h));


}

int HudMenu::getWidth()
{
//	return sprite->getTextureRect().size.width;
	return listView->getSize().width;


}

int HudMenu::getHeight()
{
//	return sprite->getTextureRect().size.height;
	return listView->getSize().height;
}

cocos2d::ui::ListView* HudMenu::getListView()
{
	return listView;
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

//	HudCursor::getInstance()->setPosition(position);

	HudCursor::getInstance()->getSprite()->removeFromParent();

	itemList[itemIndex]->getLabel()->addChild(
		HudCursor::getInstance()->getSprite()
	);

	HudCursor::getInstance()->getSprite()->setGlobalZOrder(20);
	HudCursor::getInstance()->showAnimation();

	HudCursor::getInstance()->getSprite()->setPosition(-8, 16);

	listView->scrollToItem(
		itemIndex,
		cocos2d::Vec2::ANCHOR_MIDDLE,
		cocos2d::Vec2::ANCHOR_MIDDLE
	);

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
	this->hide();

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
//	listView->cleanup();
//	listView->setContentSize(layout->getSize());
	cocos2d::Vector<cocos2d::ui::Widget*> widgetList = listView->getItems();
	listView->removeAllChildren();

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

void HudMenu::setBKImage(std::string fileName)
{
	layout->setBackGroundImage(fileName);
}
