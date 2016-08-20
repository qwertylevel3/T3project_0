#include "HudLayer.h"
#include"HudMenuItem.h"
#include"HudSender.h"
#include"HudMenu.h"
#include"HudCursor.h"

USING_NS_CC;

HudLayer::HudLayer()
{
}


HudLayer::~HudLayer()
{
}

void HudLayer::initLayer()
{
	HudMenu::getInstance()->init();
}

void HudLayer::update()
{
	for (int i = 0; i < senderList.size(); i++)
	{
		senderList[i]->updateSender();
	}
}

void HudLayer::show()
{
	HudMenu::getInstance()->show();
	HudCursor::getInstance()->show();
}

void HudLayer::hide()
{
	HudMenu::getInstance()->hide();
	HudCursor::getInstance()->hide();
}

void HudLayer::addSender(HudSender* sender)
{
	senderList.push_back(sender);

	auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();

	auto label = sender->getSenderLable();
	label->setPosition(Vec2(origin.x + 100,
		origin.y + 100 - label->getContentSize().height));

	this->addChild(label, 2);
}

void HudLayer::handleKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode)
{
	HudCursor::getInstance()->handleKeyPressed(keyCode);
}