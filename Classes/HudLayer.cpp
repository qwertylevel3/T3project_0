#include "HudLayer.h"
#include"HudMenuItem.h"
#include"HudSender.h"
#include"HudCursor.h"
#include "HudMenuSystem.h"
#include "HudStateSystem.h"
#include "DialogueManager.h"

USING_NS_CC;

HudLayer::HudLayer()
{
}


HudLayer::~HudLayer()
{
}

bool HudLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	HudMenuSystem::getInstance()->init();
	HudStateSystem::getInstance()->init();
	DialogueManager::getInstance()->init();

	DialogueManager::getInstance()->run("testDialogue");

	return true;
}

void HudLayer::update()
{
	for (size_t i = 0; i < senderList.size(); i++)
	{
		senderList[i]->updateSender();
	}
	HudMenuSystem::getInstance()->update();
	HudStateSystem::getInstance()->update();
}

void HudLayer::show()
{
	HudMenuSystem::getInstance()->show();
}

void HudLayer::hide()
{
	HudMenuSystem::getInstance()->hide();
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
