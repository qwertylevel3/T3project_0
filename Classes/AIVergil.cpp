#include "AIVergil.h"
#include "Player.h"
#include "Character.h"
#include "HudMessageBox.h"
#include "DialogueSystem.h"

AIVergil::AIVergil()
{
}

AIVergil::~AIVergil()
{
}

void AIVergil::update()
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

void AIVergil::feedback(Character* character)
{
	characterPtr->speak(L"对话不能，现在");
}

void AIVergil::handleDialogueResult(std::string dialogueName, int resultNumber)
{
	if (dialogueName=="testDialogue")
	{
		characterPtr->speak(L"对话完毕");
	}
}
