#include "AIPlayer.h"
#include "KeyController.h"
#include "GameSaveManager.h"
#include "SplashLayer.h"
#include "GameController.h"
#include "HudMessageBox.h"
#include "DialogueSystem.h"



AIPlayer::AIPlayer()
{
}


AIPlayer::~AIPlayer()
{
}

void AIPlayer::update()
{

}

void AIPlayer::lastWords()
{
	SplashLayer::getInstance()->fadeInBlack(2);
	GameSaveManager::getInstance()->increaseDieCount();
	GameSaveManager::getInstance()->save();
	DialogueSystem::getInstance()->runDialogue("playerDie",characterPtr);
}

void AIPlayer::handleDialogueResult(std::string dialogueName, int resultNumber)
{
	KeyController::getInstance()->setBlock(true);
	GameController::getInstance()->reStartGame();
}

void AIPlayer::levelUp()
{
	HudMessageBox::getInstance()->addMessage(L"��������");
}

