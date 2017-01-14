#include "RoundSystem.h"
#include "2d/CCNode.h"
#include "Character.h"
#include "Dungeon.h"
#include "Marco.h"
#include "KeyController.h"
#include "Player.h"
#include "2d/CCAnimation.h"
#include "MainLayer.h"
#include "ZOrderManager.h"
#include "base/CCEventListenerCustom.h"
#include "ToolFunction.h"

using namespace Field;

//////////////////////////////////////////////////////////////////////////

RoundHandler::RoundHandler(Character* character)
	:characterPtr(character)
	, actionPoint(1)
	, delayTime(0)
	, skipNextRound(false)
{
}

RoundHandler::~RoundHandler()
{
}

void RoundHandler::startRound()
{
	actionPoint = 1;
	delayTime = 0;
}

void RoundHandler::processAction(float dt)
{
	delayTime += dt;
	actionPoint--;

	if (actionPoint <= 0)
	{
		characterPtr->endRound();
		//如果刚刚玩家结束了回合，锁定键盘0.2m
		if (characterPtr == Player::getInstance()->getcharacterPtr())
		{
			KeyController::getInstance()->setBlock(true);
			//			RoundSystem::getInstance()->playerBlockStart();
			cocos2d::DelayTime* delayAction = cocos2d::DelayTime::create(0.2);
			cocos2d::CallFunc *callFun = cocos2d::CallFunc::create(RoundSystem::getInstance(), callfunc_selector(RoundSystem::unlockPlayerKey));
			cocos2d::Sequence *action = cocos2d::Sequence::create(delayAction, callFun, NULL);

			Player::getInstance()->getcharacterPtr()->getSprite()->runAction(action);
		}

		cocos2d::Sprite* characterSprite = characterPtr->getSprite();

		if (dt <= 0.0001)
		{
			RoundSystem::getInstance()->sendNextRoundMessage();
		}
		else
		{
			cocos2d::DelayTime* delayAction = cocos2d::DelayTime::create(dt);
			cocos2d::CallFunc *callFun = cocos2d::CallFunc::create(RoundSystem::getInstance(), callfunc_selector(RoundSystem::sendNextRoundMessage));
			cocos2d::Sequence *action = cocos2d::Sequence::create(delayAction, callFun, NULL);
			characterSprite->runAction(action);
		}
	}
}

int RoundHandler::getActionPoint()
{
	return actionPoint;
}

bool RoundHandler::isSkipNextRound()
{
	return skipNextRound;
}

void RoundHandler::setSkipNextRound(bool b)
{
	skipNextRound = b;
}

//////////////////////////////////////////////////////////////////////////

RoundSystem::RoundSystem()
{
}

RoundSystem::~RoundSystem()
{
	chooseArrow->release();
}

bool RoundSystem::init()
{
	if (!Node::init())
	{
		return false;
	}

	roundCount = 0;
	chooseArrow = cocos2d::Sprite::create("sys/chooseArrow.png");
	chooseArrow->setZOrder(ZOrderManager::chooseArrowZ);
	chooseArrow->retain();

	//	listener = cocos2d::EventListenerCustom::create("roundOver", [=](cocos2d::EventCustom* event) {
	//		nextRound();
	//	});
	//	_eventDispatcher->addEventListenerWithFixedPriority(listener, 1);
	return true;
}

void RoundSystem::initMission()
{
	curIndex = 0;
}

int RoundSystem::getRoundCount()
{
	return roundCount;
}

void RoundSystem::sendNextRoundMessage()
{
	nextRound();
}

void RoundSystem::nextIndex()
{
	curIndex++;
	if (curIndex >= allCharacter.size())
	{
		curIndex = 0;
	}
}

bool RoundSystem::isPlayer(Character* character)
{
	return character == Player::getInstance()->getcharacterPtr();
}

void RoundSystem::round()
{
	//	CCASSERT(!allCharacter.empty(), "empty character list in roundSys");

	if (allCharacter.empty())
	{
		return;
	}

	Character* curCharacter = allCharacter[curIndex];

	if (!curCharacter->isDead())
	{
		curCharacter->startRound();
		curCharacter->update();
	}

	RoundHandler* roundHandler = allCharacter[curIndex]->getRoundHandler();

	if (isPlayer(curCharacter))
	{
		playerAction();
	}
	else
	{
		NPCAction(curCharacter);
	}
}

void RoundSystem::NPCAction(Character* character)
{
	if (character->isDead())
	{
		nextRound();
	}
	else
	{
		circleOver = false;
		while (character->getActionPoint() != 0)
		{
			character->action();
		}
	}
}

void RoundSystem::playerAction()
{
	circleOver = true;
}

void RoundSystem::start()
{
	round();
}

void RoundSystem::nextRound()
{
	//	do
	//	{
	nextIndex();
	//	} while (allCharacter[curIndex]->isDead());

		//	if (isPlayer(allCharacter[curIndex]))
		//	{
		//		cocos2d::DelayTime* delayTime = cocos2d::DelayTime::create(0.2);
		//		cocos2d::CallFunc *callFun = cocos2d::CallFunc::create(this, callfunc_selector(RoundSystem::round));
		//		cocos2d::Sequence *action = cocos2d::Sequence::create(delayTime, callFun, NULL);
		//		//this->runAction(action);
		//		allCharacter[curIndex]->getSprite()->runAction(action);
		//	}
		//	else
		//	{
		//		round();
		//	}
	round();
}

void RoundSystem::addCharacter(Character* character)
{
	allCharacter.push_back(character);
}

void RoundSystem::clear()
{
	allCharacter.clear();
}

void RoundSystem::unlockPlayerKey()
{
	KeyController::getInstance()->setBlock(false);
}

bool RoundSystem::isCircleOver()
{
	return circleOver;
}