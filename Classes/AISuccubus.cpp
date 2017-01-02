#include "AISuccubus.h"
#include "Player.h"
#include "DialogueSystem.h"
#include "Player.h"
#include "HudMessageBox.h"



AISuccubus::AISuccubus()
{
	isFirst = true;
}


AISuccubus::~AISuccubus()
{
}

void AISuccubus::update()
{
	if (isFirst)
	{
		DialogueSystem::getInstance()->runDialogue("summonSuccubus");

		isFirst = false;
	}

	int viewSize = characterPtr->getViewSize();

	Character* enemyTarget = searchTargetBFS(Character::Bad);

	if (enemyTarget)
	{
		//如果和player距离过远，就跟随player
		if (getManhattanDistance(Player::getInstance()->getcharacterPtr()) > 6)
		{
			seek(Player::getInstance()->getcharacterPtr());
		}
		else
		{
			if (isInAttackArea(enemyTarget))
			{
				characterPtr->attack();
			}
			else
			{
				seek(enemyTarget);
			}
		}
	}
	else
	{
		cocos2d::Point playerCoord = Player::getInstance()->getcharacterPtr()->getMapCoord();
		if (isNear(playerCoord))
		{
			characterPtr->idle();
		}
		else
		{
			seek(Player::getInstance()->getcharacterPtr());
		}
	}

}

void AISuccubus::feedback(Character* character)
{
	DialogueSystem::getInstance()->runDialogue("talkSuccubus", this->characterPtr);
}

void AISuccubus::handleDialogueResult(std::string dialogueName, int resultNumber)
{
	Player::getInstance()->getcharacterPtr()->sufferHPEffect(-19);
	characterPtr->sufferHPEffect(100);
	characterPtr->sufferMPEffect(100);

	HudMessageBox::getInstance()->addMessage(L"你感觉身体被掏空");

}
