#include "AIPersephone.h"
#include "KeyController.h"
#include "GameSaveManager.h"
#include "SplashLayer.h"
#include "RandomNumber.h"
#include "HudMessageBox.h"
#include "ToolFunction.h"
#include "DialogueSystem.h"
#include "GameController.h"
#include "Player.h"

AIPersephone::AIPersephone()
{
	talkFlag = 0;
}

AIPersephone::~AIPersephone()
{
}

void AIPersephone::update()
{
	if (!characterPtr)
	{
		return;
	}

	if (talkFlag == 0
		&& ToolFunction::isNear8(characterPtr->getMapCoord(),
			Player::getInstance()->getcharacterPtr()->getMapCoord()))
	{
		DialogueSystem::getInstance()->runDialogue("persephoneTalk", characterPtr);
		talkFlag = 1;
	}

	//////////////////////////////////////////////////////////////////////////

	int viewSize = characterPtr->getViewSize();
	Character* targetCharacter = searchTargetBFS(Character::Good);
	if (targetCharacter)
	{
		changeOrientationTo(targetCharacter);
		if (!isInAttackArea(targetCharacter))
		{
			seek(targetCharacter);
		}
		else
		{
			int roll = RandomNumber::getInstance()->randomInt(1, 10);

			if (roll <= 2)
			{
				characterPtr->runSkill("Thunder_…¡µÁ_0_0_100");
			}
			else
			{
				characterPtr->attack();
			}
		}
	}
	else
	{
		characterPtr->idle();
	}
}

void AIPersephone::feedback(Character* character)
{
}

void AIPersephone::lastWords()
{
//	SplashLayer::getInstance()->fadeInWhite(2);
	SplashLayer::getInstance()->clearGame();
	DialogueSystem::getInstance()->runDialogue("clearGame",characterPtr);
}

void AIPersephone::handleDialogueResult(std::string dialogueName, int resultNumber)
{
	if (dialogueName == "persephoneTalk"
		&& resultNumber == -1)
	{
		for (int i = 0; i < 2; i++)
		{
			summonDemon();
		}
	}
	else if (dialogueName == "clearGame"
		&& resultNumber == -1)
	{
		KeyController::getInstance()->setBlock(true);
		GameSaveManager::getInstance()->increaseClearGameCount();
		GameSaveManager::getInstance()->increasePersephoneDieCount();
		GameSaveManager::getInstance()->increaseFirstClear();
		GameSaveManager::getInstance()->save();
		GameController::getInstance()->reStartGame();
	}
}

void AIPersephone::summonDemon()
{
	characterPtr->runSkill("Summon_’ŸªΩ_0_0_demon");
	HudMessageBox::getInstance()->addMessage(L"persephone’ŸªΩ¡À∂Òƒß");
}

void AIPersephone::castThunder()
{
	characterPtr->runSkill("Thunder_…¡µÁ_30_30_100");
	HudMessageBox::getInstance()->addMessage(L"persephone Õ∑≈¡À…¡µÁ");
}