#include "RoundSystem.h"
#include "Character.h"
#include "Dungeon.h"
#include "Marco.h"
#include "KeyController.h"
#include "Player.h"
#include "2d/CCAnimation.h"

using namespace Field;

RoundSystem::RoundSystem()
{
}

RoundSystem::~RoundSystem()
{
}

void RoundSystem::init()
{
	roundCount = 0;
}

void RoundSystem::loadStorey()
{
	int index = 0;
	Storey* storey = Dungeon::getInstance()->getStorey();
	std::list<Character* >& allStoreyCharacter = storey->getAllCharacter();
	for (std::list<Character*>::iterator iter = allStoreyCharacter.begin();
		iter != allStoreyCharacter.end();
		iter++)
	{
		allCharacter.push_back(*iter);
		//初始化加载所有character的时候，将第一个行动设为player
		if (isPlayer(*iter))
		{
			curIndex = index;
		}
		index++;
	}
}

int RoundSystem::getRoundCount()
{
	return roundCount;
}

void RoundSystem::nextRound()
{
	allCharacter[curIndex]->endRound();
	KeyController::getInstance()->setBlock(true);
	do
	{
		nextIndex();
	} while (allCharacter[curIndex]->isDead());

	roundCount++;
	allCharacter[curIndex]->startRound();

	//如果这个character在player视野内，则延迟一会，造成一种回合的假象
	cocos2d::Point coord = allCharacter[curIndex]->getMapCoord();
	if (Player::getInstance()->isInViewSize(coord))
	{
		cocos2d::DelayTime* delayTime = cocos2d::DelayTime::create(0.1);
		cocos2d::CallFunc *callFunc = cocos2d::CallFunc::create(this, callfunc_selector(RoundSystem::round));
		cocos2d::Sequence *action = cocos2d::Sequence::create(delayTime, callFunc, NULL);

		allCharacter[curIndex]->getSprite()->runAction(action);
	}
	else
	{
		round();
	}
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
	int index = curIndex;
	std::cout << roundCount << std::endl;

	Character* curCharacter = allCharacter[index];
	//更新character信息，包括buff
	curCharacter->update();

	if (isPlayer(allCharacter[index]))
	{
		//当为player character，重新解除键盘锁定，清除递归栈
		KeyController::getInstance()->setBlock(false);
		playerAction();
	}
	else
	{
		KeyController::getInstance()->setBlock(true);
		//这里下一个character会递归调用nextRound，直到为player character
		NPCAction(curCharacter);
	}

	//curCharacter->update();
}

void RoundSystem::NPCAction(Character* character)
{
	if (character->isActionAble())
	{
		character->action();

		nextRound();
	}
	else
	{
		nextRound();
	}
}

void RoundSystem::playerAction()
{
	if (!Player::getInstance()->getcharacterPtr()->isActionAble())
	{
		KeyController::getInstance()->setBlock(true);
		nextRound();
	}
}
