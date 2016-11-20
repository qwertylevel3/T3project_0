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
	chooseArrow = cocos2d::Sprite::create("chooseArrow.png");
	chooseArrow->setZOrder(ZOrderManager::chooseArrowZ);
	chooseArrow->retain();

	listener = cocos2d::EventListenerCustom::create("roundOver", [=](cocos2d::EventCustom* event) {
		nextRound();
	});
	_eventDispatcher->addEventListenerWithFixedPriority(listener, 1);
	return true;
}

void RoundSystem::loadStorey()
{
	allCharacter.clear();
	curIndex = 0;

	Field::Storey* storey = Field::Dungeon::getInstance()->getStorey();
	std::list<Character*> storeyCharacters = storey->getAllCharacter();

	for each (Character*  character in storeyCharacters)
	{
		allCharacter.push_back(character);
	}
}

int RoundSystem::getRoundCount()
{
	return roundCount;
}

void RoundSystem::sendNextRoundMessage()
{
	cocos2d::EventCustom event("roundOver");
	_eventDispatcher->dispatchEvent(&event);
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
	CCASSERT(!allCharacter.empty(), "empty character list in roundSys");

	Character* curCharacter = allCharacter[curIndex];
	curCharacter->startRound();
	curCharacter->update();

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
	while (character->getActionPoint() != 0)
	{
		character->action();
	}
}

void RoundSystem::playerAction()
{
	KeyController::getInstance()->setBlock(false);
}

void RoundSystem::start()
{
	round();
}

void RoundSystem::nextRound()
{
	if (isPlayer(allCharacter[curIndex]))
	{
		KeyController::getInstance()->setBlock(true);
	}

	do
	{
		nextIndex();
	} while (allCharacter[curIndex]->isDead());

	round();
}