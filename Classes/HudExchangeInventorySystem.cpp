#include "HudExchangeInventorySystem.h"
#include "HudMessageBox.h"
#include "HudLayer.h"
#include "HudLayer.h"
#include "KeyController.h"
#include "HudTrigGiveInv.h"
#include "HudCursor.h"
#include "HudMenuItem.h"
#include "InventoryFactory.h"
#include "ToolFunction.h"
#include "InventoryHandler.h"
#include "Player.h"
#include "HudMenu.h"

HudExchangeInventoryMenu::HudExchangeInventoryMenu()
	:HudMenu(cocos2d::Rect(0, 0, 300, 375))
{
	characterPtr = nullptr;
	titleLabel = cocos2d::Label::createWithTTF("", "fonts/arialuni.ttf", 20);
	titleLabel->setAnchorPoint(cocos2d::Vec2::ANCHOR_TOP_LEFT);
	titleLabel->setPosition(40, 400);
	layout->addChild(titleLabel);
}

HudExchangeInventoryMenu::~HudExchangeInventoryMenu()
{
}

void HudExchangeInventoryMenu::update()
{
	clear();
	if (!characterPtr)
	{
		HudMenuItem* emptyItem = new HudMenuItem("empty");
		titleLabel->setString("");
		this->addItem(emptyItem);
		return;
	}

	std::string weight = ToolFunction::int2string(characterPtr->getWeight());
	std::string sumWeight = ToolFunction::int2string(characterPtr->getSumWeight());

	titleLabel->setString(
		characterPtr->getName() +
		ToolFunction::WStr2UTF8(L"的背包") +
		"[" + sumWeight + "/" + weight + "]"
	);

	InventoryHandler* inventoryHandler = characterPtr->getInventoryHandler();

	std::map<std::string, int> inventoryMap = inventoryHandler->getAllInventory();

	std::map<std::string, int>::const_iterator iter = inventoryMap.cbegin();
	while (iter != inventoryMap.cend())
	{
		std::string cname = InventoryFactory::getInstance()->queryCname(iter->first);
		std::string count = ToolFunction::int2string(iter->second);
		std::string weight = ToolFunction::int2string(InventoryFactory::getInstance()->queryInventoryWeight(iter->first));

		HudMenuItem* inventoryItem = new HudMenuItem(
			cname + " x" + count+
			"["+weight+"kg]"
		);

		setItemTrigger(inventoryItem);
		this->addItem(inventoryItem);

		iter++;
	}
	if (itemList.empty())
	{
		HudMenuItem* emptyItem = new HudMenuItem("empty");
		this->addItem(emptyItem);
	}
	HudCursor::getInstance()->setCurMenu(this);
}

void HudExchangeInventoryMenu::handleLeft()
{
	HudExchangeInventorySystem::getInstance()->changeGive();
}

void HudExchangeInventoryMenu::handleRight()
{
	HudExchangeInventorySystem::getInstance()->changeGive();
}

void HudExchangeInventoryMenu::setCharacter(Character* character)
{
	characterPtr = character;
}

void HudExchangeInventoryMenu::setItemTrigger(HudMenuItem* item)
{
	HudTrigGiveInv* trigger = new HudTrigGiveInv();
	item->setTrigger(trigger);
}

//////////////////////////////////////////////////////////////////////////

HudExchangeInventorySystem::HudExchangeInventorySystem()
{
}

HudExchangeInventorySystem::~HudExchangeInventorySystem()
{
	leftArrow->removeFromParent();
	rightArrow->removeFromParent();

	delete menuA;
	delete menuB;
}

void HudExchangeInventorySystem::init()
{
	menuA = new HudExchangeInventoryMenu();
	menuB = new HudExchangeInventoryMenu();

	menuA->setPosition(75, 550);
	menuB->setPosition(425, 550);

	menuA->hide();
	menuB->hide();

	leftArrow = cocos2d::Sprite::create("sys/noteArrowLeft.png");
	rightArrow = cocos2d::Sprite::create("sys/noteArrowRight.png");

	leftArrow->setPosition(400, 350);
	rightArrow->setPosition(400, 350);

	leftArrow->setVisible(false);
	rightArrow->setVisible(false);

	HudLayer::getInstance()->addChild(leftArrow);
	HudLayer::getInstance()->addChild(rightArrow);
}

void HudExchangeInventorySystem::close()
{
	menuA->hide();
	menuB->hide();


	leftArrow->setVisible(false);
	rightArrow->setVisible(false);

	KeyController::getInstance()->switchCtrlToPlayer();
}

void HudExchangeInventorySystem::give()
{
	if (curGive)
	{
		AgiveB();
	}
	else
	{
		BgiveA();
	}
}

void HudExchangeInventorySystem::AgiveB()
{
	int curIndex = menuA->getCurIndex();

	std::string inventoryName = characterA->queryInventoryNameByIndex(curIndex);


	int curWeight = characterB->getWeight();
	int curSumWeight = characterB->getSumWeight();
	int inventoryWeight = InventoryFactory::getInstance()->queryInventoryWeight(inventoryName);

	if (curSumWeight+inventoryWeight>curWeight)
	{
		HudMessageBox::getInstance()->addMessage(L"超出对方负重上限");
		return;
	}

	characterA->removeInventory(inventoryName);
	characterB->addInventory(inventoryName);

	menuA->update();
	menuB->update();
	HudCursor::getInstance()->setCurMenu(menuA);
}

void HudExchangeInventorySystem::BgiveA()
{
	int curIndex = menuB->getCurIndex();

	std::string inventoryName = characterB->queryInventoryNameByIndex(curIndex);
	characterB->removeInventory(inventoryName);

	characterA->addInventory(inventoryName);

	menuA->update();
	menuB->update();
	HudCursor::getInstance()->setCurMenu(menuB);
}

void HudExchangeInventorySystem::changeGive()
{
	curGive = !curGive;

	if (curGive)
	{
		HudCursor::getInstance()->setCurMenu(menuA);
	}
	else
	{
		HudCursor::getInstance()->setCurMenu(menuB);
	}
	showArrow();
}

void HudExchangeInventorySystem::exchangeInventory(Character* A, Character* B)
{
	KeyController::getInstance()->switchCtrlToExchangeInv();

	curGive = true;

	characterA = A;
	characterB = B;

	menuA->setCharacter(A);
	menuB->setCharacter(B);

	menuA->update();
	menuB->update();

	menuB->show();
	menuA->show();

	HudCursor::getInstance()->setCurMenu(menuA);
	HudCursor::getInstance()->show();

	showArrow();
}

void HudExchangeInventorySystem::showArrow()
{
	if (curGive)
	{


		leftArrow->setVisible(false);

		rightArrow->setVisible(true);
		rightArrow->stopAllActions();
		rightArrow->setPosition(400, 350);
		rightArrow->runAction(
			cocos2d::RepeatForever::create(
				cocos2d::Sequence::create(
					cocos2d::MoveBy::create(1, cocos2d::Vec2(5, 0)),
					cocos2d::MoveBy::create(0.1, cocos2d::Vec2(-5, 0)),
					NULL
				)
			)
		);
	}
	else
	{
		rightArrow->setVisible(false);

		leftArrow->setVisible(true);
		leftArrow->stopAllActions();
		leftArrow->setPosition(400, 350);
		leftArrow->runAction(
			cocos2d::RepeatForever::create(
				cocos2d::Sequence::create(
					cocos2d::MoveBy::create(1, cocos2d::Vec2(-5, 0)),
					cocos2d::MoveBy::create(0.1, cocos2d::Vec2(5, 0)),
					NULL
				)
			)
		);
	}
}
