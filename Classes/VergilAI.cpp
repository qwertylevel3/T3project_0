#include "VergilAI.h"
#include "Player.h"
#include "Character.h"
#include "HudMessageBox.h"
#include "DialogueSystem.h"

VergilAI::VergilAI()
{
}

VergilAI::~VergilAI()
{
}

void VergilAI::update()
{
	int viewSize = characterPtr->getViewSize();

	Character* enemyTarget = searchTargetBFS(Character::Bad);

	if (enemyTarget)
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

void VergilAI::interaction()
{
	characterPtr->speak(L"暂时不能说话哦");

//	DialogueSystem::getInstance()->runDialogue("testDialogue",characterPtr);
}

void VergilAI::handleDialogueResult(std::string dialogueName, int resultNumber)
{
	if (dialogueName=="testDialogue")
	{
		characterPtr->speak(L"对话完毕");
	}
}
